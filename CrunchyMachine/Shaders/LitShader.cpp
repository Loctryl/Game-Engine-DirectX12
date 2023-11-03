#include "LitShader.h"

void LitShader::Begin(ID3D12GraphicsCommandList* list)
{
	list->SetGraphicsRootSignature(mRootSignature);
	list->SetGraphicsRootConstantBufferView(1, mPass->GetResource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool LitShader::OnCreate()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[2];

	slotRootParameter[0].InitAsConstantBufferView(0);
	slotRootParameter[1].InitAsConstantBufferView(1);

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(
		2, slotRootParameter,
		1, staticSampler,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* errorBlob = nullptr;
	D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&mSerializedRootSignature,
		&errorBlob);

	return true;
}

void LitShader::SetPassCB(XMFLOAT4X4 viewProj)
{

}

UploadBufferBase* LitShader::OnCreatePassUploadBuffer() { return new UploadBuffer<PassConstLit>(mDevice, 1, true); }

UploadBufferBase* LitShader::OnCreateObjectUploadBuffer() { return new UploadBuffer<ObjConstLit>(mDevice, 1, true); }