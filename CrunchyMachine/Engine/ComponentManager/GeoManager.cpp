#include "GeoManager.h"
#include "Resources/Color.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"

GeoManager* GeoManager::mInstance = nullptr;


GeoManager::GeoManager()
{
	mDirectX = nullptr;
}

GeoManager::GeoManager(D3DApp* mDApp)
{
	
	mInstance = new GeoManager();

	mDirectX = mDApp;
	geometries = vector<MeshGeometry*>();
}

GeoManager::~GeoManager()
{
}


GeoManager* GeoManager::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new GeoManager(D3DApp::GetInstance());
		mInstance->Init();
	}
	return mInstance;
}

void GeoManager::Init()
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


MeshGeometry* GeoManager::GetLosangeMesh()
{
	return mInstance->geometries[0];
}

MeshGeometry* GeoManager::GetSquareMesh()
{
	return mInstance->geometries[1];
}

MeshGeometry* GeoManager::GetCubeMesh()
{
	return nullptr;
}

MeshGeometry* GeoManager::CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mInstance->mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

RenderComponent* GeoManager::CreateRenderComponent(MeshGeometry* geo)
{
	return mInstance->mDirectX->CreateRenderComponent(geo);
}

void GeoManager::Render() 
{
	for (int i = 0; i < gObj.size(); i++)
	{
		mInstance->mDirectX->UpdateConstantBuffer(gObj[i]->mItem, XMLoadFloat4x4(&gObj[i]->mTransform->GetWorldMatrix()));
	}
}