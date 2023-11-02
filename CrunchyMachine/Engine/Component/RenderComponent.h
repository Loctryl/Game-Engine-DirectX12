#pragma once
#include "Engine/Component/Component.h"
#include "Resources/framework.h"

class MeshGeometry;
class Shader;

enum GEO 
{ 
	QUAD,
	LOSANGE,
	CUBE
};


class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(MeshGeometry* mesh, int shadIndex, const wchar_t* path = nullptr, string texName = "");
	RenderComponent(GEO shape, int shadIndex, const wchar_t* path = nullptr, string texName = "");

	~RenderComponent();

	MeshGeometry* mGeo = nullptr;

	Shader* mShader = nullptr;

	Texture* mTexture;
	int mTextureOffset = -1;
};

