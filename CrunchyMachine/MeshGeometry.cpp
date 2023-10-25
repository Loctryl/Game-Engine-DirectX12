#include "DirectX12/MeshGeometry.h"


MeshGeometry::MeshGeometry() { }

MeshGeometry::MeshGeometry(string n) 
{
	mName = n;
}

MeshGeometry::~MeshGeometry()
{
	DisposeUploaders();
}


void MeshGeometry::DisposeUploaders()
{
	mVertexBufferUploader = nullptr;
	mIndexBufferUploader = nullptr;
}

D3D12_VERTEX_BUFFER_VIEW MeshGeometry::VertexBufferView() const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = mVertexBufferGPU->GetGPUVirtualAddress();
	vbv.StrideInBytes = mVertexByteStride;
	vbv.SizeInBytes = mVertexBufferByteSize;
	return vbv;
}

D3D12_INDEX_BUFFER_VIEW MeshGeometry::IndexBufferView() const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = mIndexBufferGPU->GetGPUVirtualAddress();
	ibv.Format = mIndexFormat;
	ibv.SizeInBytes = mIndexBufferByteSize;
	return ibv;
}