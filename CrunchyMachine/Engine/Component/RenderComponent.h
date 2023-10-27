#pragma once
#include "DirectX12/MeshGeometry.h"
#include "DirectX12/UploadBuffer.h"


class RenderComponent
{
public:
	RenderComponent() = default;

	UINT ObjCBIndex = -1;

	MeshGeometry* Geo = nullptr;

	UploadBuffer<ObjectConstants>* mConstantBuffer = nullptr;

	//Shader* shad = nullptr;
};

