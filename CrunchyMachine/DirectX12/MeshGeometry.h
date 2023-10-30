#pragma once
#include "Resources/framework.h"


class MeshGeometry
{
public:
	// Give it a name so we can look it up by name.
	UINT mIndexCount = 0;

	string mName;

	ID3DBlob* mVertexBufferCPU = nullptr;
	ID3DBlob* mIndexBufferCPU = nullptr;
	ID3D12Resource* mVertexBufferGPU = nullptr;
	ID3D12Resource* mIndexBufferGPU = nullptr;
	ID3D12Resource* mVertexBufferUploader = nullptr;
	ID3D12Resource* mIndexBufferUploader = nullptr;

	// Data about the buffers.
	UINT mVertexByteStride = 0;
	UINT mVertexBufferByteSize = 0;
	DXGI_FORMAT mIndexFormat = DXGI_FORMAT_R16_UINT;
	UINT mIndexBufferByteSize = 0;

	// We can free this memory after we finish upload to the GPU.
	void DisposeUploaders();

	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;

	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;

	MeshGeometry();
	MeshGeometry(string name);
	~MeshGeometry();
};