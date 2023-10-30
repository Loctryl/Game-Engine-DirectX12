#pragma once

class MeshGeometry;
class Shader;


class RenderComponent
{
public:
	RenderComponent() = default;

	MeshGeometry* mGeo = nullptr;

	Shader* mShader = nullptr;
};

