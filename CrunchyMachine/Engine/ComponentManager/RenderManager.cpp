#include "RenderManager.h"
#include "Resources/Color.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"


RenderManager::RenderManager()
{
	mComponentType = RENDER;
	mComponents = std::vector<RenderComponent*>();
	mDirectX = D3DApp::GetInstance();
	geometries = vector<MeshGeometry*>();
	Init();
}

RenderManager::~RenderManager()
{
}

void RenderManager::Init()
{
	Vertex1 losVertices[] =
	{
	   { XMFLOAT3(0.0f, 0.75f, 0.0f), Color::white()},
	   { XMFLOAT3(0.25f, 0.0f, 0.25f), Color::cyan()},
	   { XMFLOAT3(0.25f, 0.0f, -0.25f), Color::red()},
	   { XMFLOAT3(-0.25f, 0.0f, -0.25f), Color::purple() },
	   { XMFLOAT3(-0.25f, 0.0f, 0.25f), Color::green() },
	   { XMFLOAT3(0.0f, -0.75f, 0.0f), Color::black() }
	};

	std::uint16_t losIndices[] = {
	   0,1,2,
	   0,2,3,
	   0,3,4,
	   0,4,1,

	   5,2,1,
	   5,3,2,
	   5,4,3,
	   5,1,4
	};

	geometries.push_back(CreateGeometry(losVertices, _countof(losVertices), losIndices, _countof(losIndices), "Losange"));

	Vertex1 quadVertices[] =
	{
	   { XMFLOAT3(0.25f, 0.25f, 0.0f), Color::cyan()},
	   { XMFLOAT3(0.25f, -0.25f, 0.0f), Color::red()},
	   { XMFLOAT3(-0.25f, -0.25f, 0.0f), Color::purple() },
	   { XMFLOAT3(-0.25f, 0.25f, 0.0f), Color::green() },
	};

	std::uint16_t quadIndices[] = {
		0,1,2,
		0,1,2,
		0,2,3
	};

	geometries.push_back(CreateGeometry(quadVertices, _countof(quadVertices), quadIndices, _countof(quadIndices), "Quad"));
}


MeshGeometry* RenderManager::GetLosangeMesh()
{
	return geometries[0];
}

MeshGeometry* RenderManager::GetSquareMesh()
{
	return geometries[1];
}

MeshGeometry* RenderManager::GetCubeMesh()
{
	return nullptr;
}

MeshGeometry* RenderManager::CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

RenderComponent* RenderManager::CreateRenderComponent(MeshGeometry* geo)
{
	return mDirectX->CreateRenderComponent(geo);
}

void RenderManager::Render() 
{
	for (int i = 0; i < mComponents.size(); i++)
	{
		mDirectX->UpdateConstantBuffer(mComponents[i], XMLoadFloat4x4(&mComponents[i]->mGameObject->mTransform->GetWorldMatrix()));
	}
}