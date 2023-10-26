#pragma once
#include "MeshGeometry.h"
#include "UploadBuffer.h"


class RenderComponent
{
public:
	RenderComponent() = default;

	UINT ObjCBIndex = -1;

	MeshGeometry* Geo = nullptr;

	UploadBuffer<ObjectConstants>* mConstantBuffer = nullptr;

	//Shader* shad = nullptr;
};

