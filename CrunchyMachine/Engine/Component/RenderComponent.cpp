#include "RenderComponent.h"
#include "Engine/Engine.h"
#include "Shaders/TextureShader.h"
#include "Shaders/Shader.h"
#include "DirectX12/Frustum.h"

RenderComponent::RenderComponent() {
	mComponentType = RENDER;
}

RenderComponent::RenderComponent(MeshGeometry* mesh, int shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	mGeo = mesh;
	mGeo->mBVolume = new BoundingBox();

	mShader = Engine::GetInstance()->mRenderManager->GetShaderById(shadIndex);

	if (path != nullptr) 
		mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
}

RenderComponent::RenderComponent(GEO shape, int shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;



	if (shape == SKYBOX) {
		mGeo = Engine::GetInstance()->mRenderManager->GetCubeMesh();

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
		case LOSANGE:
			mGeo = Engine::GetInstance()->mRenderManager->GetLosangeMesh();
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

		mShader = Engine::GetInstance()->mRenderManager->GetShaderById(shadIndex);

		if (path != nullptr && (shadIndex == 1 || shadIndex == 3))
			mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
	}
}

RenderComponent::~RenderComponent()
{
	RELPTRDX(mTexture->Resource);
	RELPTR(mTexture);
	RELPTR(mGeo);
	RELPTR(mShader);
}