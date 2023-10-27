#include "GeoManager.h"
#include "Resources/Color.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameObject.h"
#include "Transform.h"
#include "Engine/GameObjectManager.h"
#include "Camera.h"

RenderManager* RenderManager::mInstance = nullptr;


RenderManager::RenderManager()
{
	mDirectX = nullptr;
}

RenderManager::RenderManager(D3DApp* mDApp)
{
	
	mInstance = new RenderManager();

	mDirectX = mDApp;
	mGeometries = vector<MeshGeometry*>();
	mShaders = vector<Shader*>();

}

RenderManager::~RenderManager()
{
}


RenderManager* RenderManager::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new RenderManager(D3DApp::GetInstance());
		mInstance->Init();
	}
	return mInstance;
}

void RenderManager::Init()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0F), (float)mDirectX->GetAspectRatio(), 0.05F, 1000.0F));

	CreateGeometries();
	CreateShaders();

}

void RenderManager::CreateGeometries()
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

	mGeometries.push_back(CreateGeometry(losVertices, _countof(losVertices), losIndices, _countof(losIndices), "Losange"));

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

	mGeometries.push_back(CreateGeometry(quadVertices, _countof(quadVertices), quadIndices, _countof(quadIndices), "Quad"));
}

void RenderManager::CreateShaders()
{
	ShaderBasic* shadbase = new ShaderBasic();
	mInstance->mDirectX->CreateShader(shadbase, L"Shaders\\VertexShader.hlsl");
	mShaders.push_back(shadbase);

	ShaderTEST* shad = new ShaderTEST();
	mInstance->mDirectX->CreateShader(shad, L"Shaders\\PixelShader.hlsl");
	mShaders.push_back(shad);
}


MeshGeometry* RenderManager::GetLosangeMesh()
{
	return mInstance->mGeometries[0];
}

MeshGeometry* RenderManager::GetSquareMesh()
{
	return mInstance->mGeometries[1];
}

MeshGeometry* RenderManager::GetCubeMesh()
{
	return nullptr;
}

Shader* RenderManager::GetShaderById(int index)
{
	return mShaders[index];
}

MeshGeometry* RenderManager::CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mInstance->mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

RenderComponent* RenderManager::CreateRenderComponent(MeshGeometry* geo, Shader* shad)
{
	return mInstance->mDirectX->CreateRenderComponent(geo, shad);
}

void RenderManager::Render() 
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GameObjectManager::GetInstance()->GetCamera()->GetView() * XMLoadFloat4x4(&mProjMatrix)));

	for (int i = 0; i < mShaders.size(); i++)
	{
		mShaders[i]->SetPassCB(viewProj);

		mShaders[i]->UpdatePass();
		//mInstance->mDirectX->UpdateConstantBuffer(gObj[i]->mItem, XMLoadFloat4x4(&gObj[i]->mTransform->GetWorldMatrix()));
	}
}