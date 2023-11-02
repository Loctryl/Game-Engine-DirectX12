#include "RenderComponent.h"
#include "Engine/Engine.h"
#include "Shaders/TextureShader.h"
#include "Shaders/Shader.h"

RenderComponent::RenderComponent() {
	mComponentType = RENDER;
}

RenderComponent::RenderComponent(MeshGeometry* mesh, int shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

	mGeo = mesh;
	mShader = Engine::GetInstance()->mRenderManager->GetShaderById(shadIndex);

	if (path != nullptr) {
		mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
	}
}

RenderComponent::RenderComponent(GEO shape, int shadIndex, const wchar_t* path, string texName)
{
	mComponentType = RENDER;

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
	default:
		break;
	}

	mShader = Engine::GetInstance()->mRenderManager->GetShaderById(shadIndex);

	if (path != nullptr) {
		mTexture = Engine::GetInstance()->mRenderManager->CreateTexture(texName, path, &mTextureOffset);
	}
}

RenderComponent::~RenderComponent()
{
	delete mGeo;
	delete mShader;
}