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
	void Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh); //meshGeometry definition in features/geometry
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

bool Shader::Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvDescriptor, BYTE* src, int size)
{
	return false;
}

void Shader::Destroy()
{
}

void Shader::UpdatePass()
{
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
	list->SetGraphicsRootConstantBufferView(2, mPass->Resource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Shader::End(ID3D12GraphicsCommandList* list)
{
}

void Shader::AddObject()
{
	int count = (int)mObjects.size();

	CD3DX12_CPU_DESCRIPTOR_HANDLE handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	handle.Offset(count + 2, mDescriptorSize);

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
	return false;
}

UploadBufferBase* ShaderBasic::OnCreatePassUploadBuffer(int& size)
{
	return nullptr;
}

UploadBufferBase* ShaderBasic::OnCreateObjectUploadBuffer(int& size)
{
	return nullptr;
}
