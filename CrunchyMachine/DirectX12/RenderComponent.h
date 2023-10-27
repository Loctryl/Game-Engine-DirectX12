#pragma once

class MeshGeometry;
class Shader;


class RenderComponent
{
public:
	RenderComponent() = default;

	MeshGeometry* mGeo = nullptr;

	//UploadBuffer<ObjectConstants>* mConstantBuffer = nullptr;

	Shader* mShader = nullptr;
};

