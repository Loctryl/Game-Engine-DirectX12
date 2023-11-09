#include "RenderComponent.h"
#include "Engine/Engine.h"
#include "Shaders/Shader.h"

RenderComponent::RenderComponent() {
	mComponentType = RENDER;
	mGeo = nullptr;
	mTexture = nullptr;
	mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
}

RenderComponent::RenderComponent(MeshGeometry* mesh, SHAD shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	mGeo = mesh;
	mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
	mShader = Engine::GetInstance()->mRenderManager->GetShader(shadIndex);

	if (path != nullptr) 
		mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
}

RenderComponent::RenderComponent(GEO shape, SHAD shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	if (shadIndex == SKYBOX) {
		mIsDestructible = false;
		mGeo = Engine::GetInstance()->mRenderManager->GetSphereMesh();

		mShader = Engine::GetInstance()->mRenderManager->GetSkyShader();

		if (path != nullptr)
			mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset, true);
	}
	else 
	{
		// Gets the mesh of prebuild geometries
		switch (shape)
		{
		case QUAD:
			mGeo = Engine::GetInstance()->mRenderManager->GetSquareMesh();
			break;
		case LOS:
			mGeo = Engine::GetInstance()->mRenderManager->GetLosMesh();
			break;
		case CUBE:
			mGeo = Engine::GetInstance()->mRenderManager->GetCubeMesh();
			break;
		case SPHERE:
			mGeo = Engine::GetInstance()->mRenderManager->GetSphereMesh();
			break;
		default:
			break;
		}

		mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);

		mShader = Engine::GetInstance()->mRenderManager->GetShader(shadIndex);

		if (path != nullptr && shadIndex != 0 && shadIndex != 2)
			mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
	}
}

RenderComponent::~RenderComponent()
{
	RELPTRDX(mTexture->Resource);
	RELPTR(mTexture);
	RELPTR(mShader);
	RELPTR(mGeo);
}

void RenderComponent::SetColor(XMFLOAT4 newColor) { mColor = newColor; }