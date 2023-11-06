#include "LitTextureShader.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/Transform.h"

void LitTextureShader::Begin(ID3D12GraphicsCommandList* list)
{
	list->SetGraphicsRootSignature(mRootSignature);
	list->SetGraphicsRootConstantBufferView(2, mPass->GetResource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool LitTextureShader::OnCreate()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[3];
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[1].InitAsConstantBufferView(0);
	slotRootParameter[2].InitAsConstantBufferView(1);

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(
		3, slotRootParameter,
		1, staticSampler,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* errorBlob = nullptr;
	D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&mSerializedRootSignature,
		&errorBlob);

	return true;
}

void LitTextureShader::SetPassCB()
{
	mPc.viewProj = GameObjectManager::GetInstance()->GetCamera()->GetViewProjTranspose();
	mPc.eyePos = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetPosition();
	mPc.diffuseAlbedo = XMFLOAT4(0.5f, 0.6f, 0.8f, 1.0f);
	mPc.roughness = 0.5f;

	mPc.lightColor = XMFLOAT4(0.9f, 0.9f, 0.7f, 1.0f);
	mPc.lightDir = XMFLOAT3(-0.5f, -1.0f, 1.0f);
}

UploadBufferBase* LitTextureShader::OnCreatePassUploadBuffer() { return new UploadBuffer<PassConstLitTex>(mDevice, 1, true); }

UploadBufferBase* LitTextureShader::OnCreateObjectUploadBuffer() { return new UploadBuffer<ObjConstLitTex>(mDevice, 1, true); }