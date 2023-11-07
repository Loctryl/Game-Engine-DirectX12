#include "RenderComponent.h"
#include "Engine/Engine.h"
#include "Shaders/TextureShader.h"
#include "Shaders/Shader.h"
#include "DirectX12/Frustum.h"

RenderComponent::RenderComponent() {
	mComponentType = RENDER;

	mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
}

RenderComponent::RenderComponent(MeshGeometry* mesh, SHAD shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	mGeo = mesh;
	mGeo->mBVolume = new BoundingBox();

	mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);
		
	mShader = Engine::GetInstance()->mRenderManager->GetShader(shadIndex);

	if (path != nullptr) 
		mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
}

RenderComponent::RenderComponent(GEO shape, SHAD shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	if (shadIndex == SKYBOX) {
		mGeo = Engine::GetInstance()->mRenderManager->GetSphereMesh();
		//mGeo->mBVolume = new BoundingSkyBox();

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

		mColor = XMFLOAT4(1.f, 1.f, 1.f, 1.f);

		mShader = Engine::GetInstance()->mRenderManager->GetShader(shadIndex);

		if (path != nullptr && (shadIndex == 1 || shadIndex == 3))
			mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
	}
}

RenderComponent::~RenderComponent()
{
	RELPTRDX(mTexture->Resource);
	RELPTR(mTexture);
	RELPTR(mShader);
}

void RenderComponent::SetColor(XMFLOAT4 newcolor) { mColor = newcolor; }