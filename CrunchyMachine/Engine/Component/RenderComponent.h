#pragma once
#include "Engine/Component/Component.h"
#include "EngineResources/framework.h"
#include "DirectX12/MeshGeometry.h"

class Shader;
class FrustumCulling;
class BoundingVolume;

// To select a mesh
enum GEO 
{ 
	QUAD,
	LOS,
	CUBE,
	SPHERE,
	SCORE
};

// To select a shader
enum SHAD
{
	COLOR,
	TEXTURE, 
	LIT_COLOR, 
	LIT_TEXTURE,
	ELEMENT_UI,
	STATIC_UI,
	SKYBOX
};


// This component stores a geometry and a shader for a game object to be rendered.
// If set, it also manages the texture.
class RenderComponent : public Component
{
public:
	XMFLOAT4 mColor;

	MeshGeometry* mGeo;

	Shader* mShader = nullptr;

	Texture* mTexture;
	int mTextureOffset = -1;

	bool mIsDestructible = true;
	
	RenderComponent();
	RenderComponent(MeshGeometry* mesh, SHAD shadIndex = LIT_COLOR, const wchar_t* path = nullptr, string texName = "");
	RenderComponent(GEO shape, SHAD shadIndex = LIT_COLOR, const wchar_t* path = nullptr, string texName = "");

	~RenderComponent() override;

	void SetColor(XMFLOAT4 newColor);
};