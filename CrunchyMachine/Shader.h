#pragma once
#include "Resources/framework.h"
#include "DirectX12/UploadBuffer.h"
#include "DirectX12/D3DApp.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	bool Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvDescriptor, const wchar_t* path);
	virtual bool OnCreate() = 0;

	virtual UploadBufferBase* OnCreatePassUploadBuffer() = 0;
	virtual UploadBufferBase* OnCreateObjectUploadBuffer() = 0;
	virtual ConstantBuffer* GetPassCB() = 0;
	virtual ConstantBuffer* GetObjectCB() = 0;
	virtual void SetPassCB(XMFLOAT4X4 viewProj) = 0;
	virtual void SetObjectCB(XMFLOAT4X4 world) = 0;;

	void Destroy();

	void UpdatePass();
	void UpdateObject();

	void Reset();
	void Begin(ID3D12GraphicsCommandList* list);
	void Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh);
	//void End(ID3D12GraphicsCommandList* list);

protected:
	void AddObject();

public:
	static ID3DBlob* Compile(const wchar_t* path, std::string entrypoint, std::string target);

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


class ShaderBasic : public Shader 
{
public:
	struct PassConstBasic : public ConstantBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstantsBasic : public ConstantBuffer {
		XMFLOAT4X4 world;
	};

	ShaderBasic();
	virtual ~ShaderBasic();

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstantBuffer* GetPassCB() { return &mPc; }
	virtual ConstantBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB(XMFLOAT4X4 viewProj) { mPc.viewProj = viewProj; }
	virtual void SetObjectCB(XMFLOAT4X4 world) { mOc.world = world; }

	PassConstBasic mPc;
	ObjConstantsBasic mOc;
};


class ShaderTEST : public Shader
{
public:
	struct PassConstBasic : public ConstantBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstantsBasic : public ConstantBuffer {
		XMFLOAT4X4 world;
	};

	ShaderTEST();
	virtual ~ShaderTEST();

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstantBuffer* GetPassCB() { return &mPc; }
	virtual ConstantBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB(XMFLOAT4X4 viewProj) { mPc.viewProj = viewProj; }
	virtual void SetObjectCB(XMFLOAT4X4 world) { mOc.world = world; }

	PassConstBasic mPc;
	ObjConstantsBasic mOc;
};