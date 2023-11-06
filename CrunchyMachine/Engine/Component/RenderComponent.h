#pragma once
#include "Engine/Component/Component.h"
#include "EngineResources/framework.h"
#include "DirectX12/MeshGeometry.h"


class Shader;
class FrustumCulling;
class BoundingVolume;

enum GEO 
{ 
	QUAD,
	LOSANGE,
	CUBE,
	SPHERE,
	SKYBOX
};



// This component stores a geometry and a shader for a game object to be rendered.
// If set, it also manages the texture.
class RenderComponent : public Component
{
public:
	RenderComponent();
	RenderComponent(MeshGeometry* mesh, int shadIndex = 0, const wchar_t* path = nullptr, string texName = "");
	RenderComponent(GEO shape, int shadIndex = 0, const wchar_t* path = nullptr, string texName = "");

	~RenderComponent();

	MeshGeometry* mGeo;

	Shader* mShader = nullptr;

	Texture* mTexture;
	int mTextureOffset = -1;
};

