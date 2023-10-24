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

			/*upload buffer base*/
	//virtual UploadBuffer<>* OnCreatePassUploadBuffer(int& size) = 0;
	//virtual UploadBuffer<>* OnCreateObjectUploadBuffer(int& size) = 0;
	
	virtual UploadBuffer<ObjectConstants>* GetPassCB() = 0;
	virtual UploadBuffer<ObjectConstants>* GetObjectCB() = 0;

	void Destroy();

	void UpdatePass();
	void UpdateObject();

	void Reset();
	void Begin(ID3D12GraphicsCommandList* list);
	//void Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh); //meshGeometry definition in features/geometry
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
		/*upload buffer base*/
	//UploadBufferBase* mPass;
	//std::vector<UploadBufferBase> mObjects;
	ID3D12RootSignature* mRootSignature;
	ID3DBlob* mVS;
	ID3DBlob* mPS;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;
	ID3D12PipelineState* mPso;
	int mIndex;

};

