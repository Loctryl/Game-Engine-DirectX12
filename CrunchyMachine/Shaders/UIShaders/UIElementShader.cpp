#include "UIElementShader.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/Transform.h"

void UIElementShader::Begin(ID3D12GraphicsCommandList* list)
{
	list->SetGraphicsRootSignature(mRootSignature);
	list->SetGraphicsRootConstantBufferView(2, mPass->GetResource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool UIElementShader::OnCreate()
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

void UIElementShader::SetPassCB()
{
	mPc.mViewProj = GameObjectManager::GetInstance()->GetCamera()->GetOrthoViewProjTranspose();
}

void UIElementShader::SetObjectCB(RenderComponent* renderItem)
{
	mOc.mWorld = renderItem->mGameObject->mTransform->GetSuperWorldMatrixTranspose();
	mOc.mColor = renderItem->mColor;
	mOc.mDigit = renderItem->mGameObject->mDigit;
	mOc.mDivider = renderItem->mGameObject->mDivider;
}

UploadBufferBase* UIElementShader::OnCreatePassUploadBuffer() { return new UploadBuffer<PassConstUI>(mDevice, 1, true); }

UploadBufferBase* UIElementShader::OnCreateObjectUploadBuffer() { return new UploadBuffer<ObjConstUI>(mDevice, 1, true); }