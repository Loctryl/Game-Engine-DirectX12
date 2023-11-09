#pragma once
#include "EngineResources/framework.h"

class BoundingVolume;

//This class stores the necessary resources to display a geometry and provides getters for them.
class MeshGeometry
{
public:
	string mName;

	UINT mIndexCount = 0;
	int mVertexCount = 0;

	ID3DBlob* mVertexBufferCPU = nullptr;
	ID3DBlob* mIndexBufferCPU = nullptr;
	ID3D12Resource* mVertexBufferGPU = nullptr;
	ID3D12Resource* mIndexBufferGPU = nullptr;
	ID3D12Resource* mVertexBufferUploader = nullptr;
	ID3D12Resource* mIndexBufferUploader = nullptr;

	UINT mVertexByteSize = 0;
	UINT mVertexBufferByteSize = 0;
	DXGI_FORMAT mIndexFormat = DXGI_FORMAT_R16_UINT;
	UINT mIndexBufferByteSize = 0;


	D3D12_VERTEX_BUFFER_VIEW VertexBufferView()const;

	D3D12_INDEX_BUFFER_VIEW IndexBufferView()const;

	MeshGeometry() = default;
	MeshGeometry(string name);

	~MeshGeometry();
};