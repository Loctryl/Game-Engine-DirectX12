#include "DirectX12/MeshGeometry.h"

MeshGeometry::MeshGeometry(string n) 
{ 
	mName = n;
}

MeshGeometry::~MeshGeometry()
{
	RELPTRDX(mIndexBufferUploader);
	RELPTRDX(mVertexBufferUploader);

	RELPTRDX(mIndexBufferGPU);
	RELPTRDX(mVertexBufferGPU);

	RELPTRDX(mIndexBufferCPU);
	RELPTRDX(mVertexBufferCPU);
}

D3D12_VERTEX_BUFFER_VIEW MeshGeometry::VertexBufferView() const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = mVertexBufferGPU->GetGPUVirtualAddress();
	vbv.StrideInBytes = mVertexByteSize;
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