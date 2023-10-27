#include "TextureShader.h"

TextureShader::TextureShader()
{
}

TextureShader::~TextureShader()
{
}

bool TextureShader::OnCreate()
{
	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[2];
	// Create a single descriptor table of CBVs => for texture
	//CD3DX12_DESCRIPTOR_RANGE cbvTable;
	//cbvTable.Init(
	//	D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
	//	2,
	//	0);
	slotRootParameter[0].InitAsConstantBufferView(0);
	slotRootParameter[1].InitAsConstantBufferView(1);
	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter,
		0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&mSerializedRootSignature,
		&errorBlob);

	return true;
}

UploadBufferBase* TextureShader::OnCreatePassUploadBuffer()
{
	return new UploadBuffer<PassConstBasic>(mDevice, 1, true);
}

UploadBufferBase* TextureShader::OnCreateObjectUploadBuffer()
{
	return new UploadBuffer<ObjConstantsBasic>(mDevice, 1, true);
}
