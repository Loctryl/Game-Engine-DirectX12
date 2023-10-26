#pragma once
#include "MeshGeometry.h"
#include "UploadBuffer.h"


class RenderComponent
{
public:
	RenderComponent() = default;

	MeshGeometry* Geo = nullptr;

	UploadBuffer<ObjectConstants>* mConstantBuffer = nullptr;

	//Shader* shad = nullptr;
};

