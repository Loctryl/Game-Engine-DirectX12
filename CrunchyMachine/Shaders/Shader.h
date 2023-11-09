#pragma once
#include "EngineResources/framework.h"
#include "Shaders/UploadBuffer.h"
#include "DirectX12/D3DApp.h"

//static sampler declaration
const CD3DX12_STATIC_SAMPLER_DESC staticSampler[] = { 
	{
	0, // point Wrap
	D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressU
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressV
	D3D12_TEXTURE_ADDRESS_MODE_WRAP // addressW
	},

	{
	1, // pointClamp
	D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // adressU
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressv
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP //adressW
	},

	{
	2, // linearWrap
	D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressU
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressV
	D3D12_TEXTURE_ADDRESS_MODE_WRAP // adressW
	},

	{
	3, // linearClamp
	D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressU
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressV
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP // addressW
	},

	{
	4, // anisotropicWrap
	D3D12_FILTER_ANISOTROPIC, // filter
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressU
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressV
	D3D12_TEXTURE_ADDRESS_MODE_WRAP, // addressW
	0.0f, // mipLODBias
	8
	},

	{
	5, // anisotropicClamp
	D3D12_FILTER_ANISOTROPIC, // filter
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressU
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressV
	D3D12_TEXTURE_ADDRESS_MODE_CLAMP, // addressW
	0.0f, // mipLODBias
	8
	}
};


// Base class for all shaders.
// Provides base fonctions needed and manages root signature and PSO for rendering.
class Shader
{
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
	ID3D12PipelineState* mPso;
	int mIndex;
	
public:
	Shader();
	virtual ~Shader();

	// Compile the HLSL shader and creates the PSO
	bool Create(ID3D12Device* device, ID3D12DescriptorHeap* cbvHeap, const wchar_t* path, bool defaultPso);

	// Creates a root signature specific for the shader
	virtual bool OnCreate() = 0;

	static ID3DBlob* Compile(const wchar_t* path, std::string entrypoint, std::string target);

	void AddObject();
	
	virtual UploadBufferBase* OnCreatePassUploadBuffer() = 0;
	virtual UploadBufferBase* OnCreateObjectUploadBuffer() = 0;
	virtual ConstBuffer* GetPassCB() = 0;
	virtual ConstBuffer* GetObjectCB() = 0;
	virtual void SetPassCB() = 0;
	virtual void SetObjectCB(RenderComponent* renderItem) = 0;
	
	virtual void Begin(ID3D12GraphicsCommandList* list) = 0;
	
	inline void UpdatePass() { mPass->CopyData(GetPassCB()); };
	inline void UpdateObject() { mObjects[mIndex]->CopyData(GetObjectCB()); }
	
	void Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh, int textureIndex);

	inline void Reset() { mIndex = 0; }
	void Destroy();
};



// Basic color shader
class ColorShader : public Shader 
{
public:
	struct PassConstColor : public ConstBuffer {
		XMFLOAT4X4 mViewProj;
	};

	struct ObjConstColor : public ConstBuffer {
		XMFLOAT4X4 mWorld;
		XMFLOAT4 mColor;
	};

	ColorShader() = default;
	~ColorShader() override = default;

	bool OnCreate() override;
	UploadBufferBase* OnCreatePassUploadBuffer() override;
	UploadBufferBase* OnCreateObjectUploadBuffer() override;
	inline ConstBuffer* GetPassCB() override { return &mPc; }
	inline ConstBuffer* GetObjectCB() override { return &mOc; }
	void SetPassCB() override;
	void SetObjectCB(RenderComponent* renderItem) override;

	void Begin(ID3D12GraphicsCommandList* list) override;

	PassConstColor mPc;
	ObjConstColor mOc;
};