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
	mPc.mViewProj = GameObjectManager::GetInstance()->GetCamera()->GetViewProjTranspose();
	mPc.mEyePos = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetWorldPosition();
	mPc.mDiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPc.mRoughness = 0.5f;

	mPc.mLightColor = XMFLOAT4(219.f / 255.f, 58.f / 255.f, 33.f / 255.f, 1.0f);
	mPc.mLightDir = XMFLOAT3(1.0f, 0.0f, 0.0f);
}

void LitTextureShader::SetObjectCB(RenderComponent* renderItem)
{
	mOc.mWorld = renderItem->mGameObject->mTransform->GetSuperWorldMatrixTranspose();
	mOc.mColor = renderItem->mColor;
}

UploadBufferBase* LitTextureShader::OnCreatePassUploadBuffer() { return new UploadBuffer<PassConstLitTex>(mDevice, 1, true); }

UploadBufferBase* LitTextureShader::OnCreateObjectUploadBuffer() { return new UploadBuffer<ObjConstLitTex>(mDevice, 1, true); }