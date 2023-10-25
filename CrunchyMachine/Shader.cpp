#pragma once
#include "Resources/framework.h"
#include "DirectX12/UploadBuffer.h"
#include "DirectX12/D3DApp.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	bool Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvDescriptor, BYTE* src, int size);
	virtual bool OnCreate() = 0;

	virtual UploadBufferBase* OnCreatePassUploadBuffer(int& size) = 0;
	virtual UploadBufferBase* OnCreateObjectUploadBuffer(int& size) = 0;
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
	static ID3DBlob* Compile(BYTE* buffer, int size, std::string entrypoint, std::string target);

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
}

bool Shader::Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvHeap, BYTE* src, int size)
{
	mDevice = Device;
	mCbvHeap = CbvHeap;
	mDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	mVS = Compile(src, size, "VS", "vs_5_0");
	if (mVS == nullptr) {
		Destroy();
		return false;
	}
	
	mPS = Compile(src, size, "PS", "ps_5_0");
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


	CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	handle.Offset(1, mDescriptorSize);
	int cbSize;
	UploadBufferBase* UB = OnCreatePassUploadBuffer(cbSize);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = UB->Resource()->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = ((cbvDesc.SizeInBytes) + 255) & ~255;
	mDevice->CreateConstantBufferView(&cbvDesc, handle);
	mPass = UB;


	//create pso

}

void Shader::Destroy()
{
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
}

void Shader::AddObject()
{
	int count = (int)mObjects.size();

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	handle.Offset(0, mDescriptorSize);

	int cbSize;
	UploadBufferBase* UB = OnCreateObjectUploadBuffer(cbSize);

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = UB->Resource()->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = ((cbvDesc.SizeInBytes) + 255) & ~255;
	mDevice->CreateConstantBufferView(&cbvDesc, handle);

	mObjects.push_back(UB);

}

ID3DBlob* Shader::Compile(BYTE* buffer, int size, std::string entrypoint, std::string target)
{
	return nullptr;
}


class ShaderBasic : public Shader {
public:
	struct PassConstBasic : public ConstantBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstantsBasic : public ConstantBuffer {
		XMFLOAT4 viewProj;
	};

	ShaderBasic();
	virtual ~ShaderBasic();

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer(int& size);
	virtual UploadBufferBase* OnCreateObjectUploadBuffer(int& size);
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
	// Create a single descriptor table of CBVs.
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(
		D3D12_DESCRIPTOR_RANGE_TYPE_CBV,
		2, // Number of descriptors in table
		0);// base shader register arguments are bound to for this root parameter
	slotRootParameter[0].InitAsDescriptorTable(
		1, // Number of ranges
		&cbvTable); // Pointer to array of ranges

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

UploadBufferBase* ShaderBasic::OnCreatePassUploadBuffer(int& size)
{
	return nullptr;
}

UploadBufferBase* ShaderBasic::OnCreateObjectUploadBuffer(int& size)
{
	return nullptr;
}
