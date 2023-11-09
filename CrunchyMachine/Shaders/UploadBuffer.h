#pragma once
#include "EngineResources/framework.h"

// Template struct for UploadBuffer
struct ConstBuffer {
};

// Helper class to update constant buffers given to shaders
class UploadBufferBase {
public:
	UploadBufferBase() = default;
	virtual ~UploadBufferBase() = default;

	ID3D12Resource* GetResource() const { return mUpload; }

	BYTE* GetMappedData() const { return mData;}

	inline void CopyData(ConstBuffer* pCB) const { memcpy(mData, pCB, mElementByteSize); }

protected:
	ID3D12Resource* mUpload;
	BYTE* mData;
	UINT mElementByteSize;
	bool mIsConstantBuffer;
};

template<typename T>
class UploadBuffer : public UploadBufferBase
{
public:
	UploadBuffer(ID3D12Device* device, UINT elementCount, bool isConstantBuffer) 
	{
		mIsConstantBuffer = isConstantBuffer;
		mElementByteSize = sizeof(T);

		if (isConstantBuffer)
			mElementByteSize = (sizeof(T) + 255) & ~255;

		device->CreateCommittedResource(
			&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
			D3D12_HEAP_FLAG_NONE,
			&CD3DX12_RESOURCE_DESC::Buffer(mElementByteSize * elementCount),
			D3D12_RESOURCE_STATE_GENERIC_READ,
			nullptr,
			IID_PPV_ARGS(&mUpload));

		mUpload->Map(0, nullptr, reinterpret_cast<void**>(&mData));
	}

	UploadBuffer(const UploadBuffer& rhs) = delete;

	UploadBuffer& operator=(const UploadBuffer& rhs) = delete;

	~UploadBuffer() override
	{
		if (mUpload != nullptr)
			mUpload->Unmap(0, nullptr);

		RELPTR(mUpload);
		RELPTR(mData);
	}
};

