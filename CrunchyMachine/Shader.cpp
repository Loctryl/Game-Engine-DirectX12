#pragma once
#include "Resources/framework.h"
#include "DirectX12/UploadBuffer.h"
#include "DirectX12/D3DApp.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	bool Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvDescriptor, const char* path);
	virtual bool OnCreate() = 0;

	virtual UploadBufferBase* OnCreatePassUploadBuffer() = 0;
	virtual UploadBufferBase* OnCreateObjectUploadBuffer() = 0;
	virtual ConstantBuffer* GetPassCB() = 0;
	virtual ConstantBuffer* GetObjectCB() = 0;

	void Destroy();

	void UpdatePass();
	void UpdateObject();

	void Reset();
	void Begin(ID3D12GraphicsCommandList* list);
	void Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh);
	void End(ID3D12GraphicsCommandList* list);

protected:
	void AddObject();

public:
	static ID3DBlob* Compile(const char* path, std::string entrypoint, std::string target);

protected:
	ID3D12Device* mDevice;
	ID3D12DescriptorHeap* mCbvHeap;
	UINT mDescriptorSize;

	ID3DBlob* mSerializedRootSignature;
	UploadBufferBase* mPass;
	std::vector<UploadBufferBase*> mObjects;
	ID3D12RootSignature* mRootSignature;
	ID3DBlob* mVS;
	ID3DBlob* mPS;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	ID3D12PipelineState* mPso;
	int mIndex;

};

Shader::Shader() {
	mDevice = nullptr;
	mCbvHeap = nullptr;
	mDescriptorSize = 0;
	mSerializedRootSignature = nullptr;
	mPass = nullptr;
	mRootSignature = nullptr;
	mVS = nullptr;
	mPS = nullptr;
	mPso = nullptr;
	mIndex = 0;
}

Shader::~Shader()
{
	Destroy();
}

bool Shader::Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvHeap, const char* path)
{
	mDevice = Device;
	mCbvHeap = CbvHeap;
	mDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	mVS = Compile(path, "VS", "vs_5_0");
	if (mVS == nullptr) {
		Destroy();
		return false;
	}

	mPS = Compile(path, "PS", "ps_5_0");
	if (mPS == nullptr) {
		Destroy();
		return false;
	}

	if (!OnCreate()) {
		Destroy();
		return false;
	}

	HRESULT hRes = mDevice->CreateRootSignature(0, mSerializedRootSignature->GetBufferPointer(), mSerializedRootSignature->GetBufferSize(), IID_PPV_ARGS(&mRootSignature));

	AddObject();
	mPass = OnCreatePassUploadBuffer();
	 


	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size()
	};
	psoDesc.pRootSignature = mRootSignature;
	psoDesc.VS =
	{
	reinterpret_cast<BYTE*>(mVS->GetBufferPointer()),

	mVS->GetBufferSize()
	};
	psoDesc.PS =
	{
	reinterpret_cast<BYTE*>(mPS->GetBufferPointer()),
	mPS->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.SampleDesc.Quality = 0;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	mDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPso));

}

void Shader::Destroy()
{
	//release tt 
}

void Shader::UpdatePass()
{
	mPass->CopyData(GetPassCB());
}

void Shader::UpdateObject()
{
	mObjects[mIndex]->CopyData(GetObjectCB());
}

void Shader::Reset()
{
	mIndex = 0;
}

void Shader::Begin(ID3D12GraphicsCommandList* list)
{
	list->SetGraphicsRootSignature(mRootSignature);
	list->SetGraphicsRootConstantBufferView(1, mPass->Resource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void Shader::Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh)
{
	D3D12_VERTEX_BUFFER_VIEW vbv = mesh->VertexBufferView();
	D3D12_INDEX_BUFFER_VIEW ibv = mesh->IndexBufferView();
	list->IASetVertexBuffers(0, 1, &vbv);
	list->IASetIndexBuffer(&ibv);

	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	tex.Offset(0, mDescriptorSize);
	list->SetGraphicsRootDescriptorTable(0, tex);

	list->SetGraphicsRootConstantBufferView(0, mObjects[mIndex]->Resource()->GetGPUVirtualAddress());

	list->DrawIndexedInstanced(mesh->mIndexCount, 1, 0, 0, 0);

	mIndex++;
	if (mIndex == mObjects.size())
		AddObject();
}

void Shader::End(ID3D12GraphicsCommandList* list)
{
	//
}

void Shader::AddObject()
{
	int count = (int)mObjects.size();

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	handle.Offset(0, mDescriptorSize);

	int cbSize;
	UploadBufferBase* UB = OnCreateObjectUploadBuffer();

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = UB->Resource()->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = ((cbvDesc.SizeInBytes) + 255) & ~255;
	mDevice->CreateConstantBufferView(&cbvDesc, handle);

	mObjects.push_back(UB);

}

ID3DBlob* Shader::Compile(const char* path, std::string entrypoint, std::string target)
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	HRESULT hr = S_OK;
	ID3DBlob* byteCode = nullptr;
	ID3DBlob* errors;

	hr = D3DCompileFromFile( L"path", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode,
		&errors);
	// Output errors to debug window.
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());
	return byteCode;
}


class ShaderBasic : public Shader {
public:
	struct PassConstBasic : public ConstantBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstantsBasic : public ConstantBuffer {
		XMFLOAT4 world;
	};

	ShaderBasic();
	virtual ~ShaderBasic();

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstantBuffer* GetPassCB() { return &mPc; }
	virtual ConstantBuffer* GetObjectCB() { return &mOc; }

	PassConstBasic mPc;
	ObjConstantsBasic mOc;
};

ShaderBasic::ShaderBasic()
{
}

ShaderBasic::~ShaderBasic()
{
}

bool ShaderBasic::OnCreate()
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
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter,
		0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&mSerializedRootSignature,
		&errorBlob);
}

UploadBufferBase* ShaderBasic::OnCreatePassUploadBuffer()
{
	return new UploadBuffer<PassConstBasic>(mDevice, 1, true);
}

UploadBufferBase* ShaderBasic::OnCreateObjectUploadBuffer()
{
	return new UploadBuffer<ObjConstantsBasic>(mDevice, 1, true);
}
