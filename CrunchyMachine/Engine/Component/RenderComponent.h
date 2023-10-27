#pragma once
#include "DirectX12/MeshGeometry.h"
#include "DirectX12/UploadBuffer.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/Component.h"


class RenderComponent : Component
{
public:
	RenderComponent();

	UINT ObjCBIndex = -1;

	MeshGeometry* Geo = nullptr;

	UploadBuffer<ObjectConstants>* mConstantBuffer = nullptr;

	//Shader* shad = nullptr;
};

