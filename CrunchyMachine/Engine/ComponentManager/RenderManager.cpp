#include "RenderManager.h"
#include "Resources/Color.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Shaders/TextureShader.h"


RenderManager::RenderManager()
{
	mComponentType = RENDER;
	mComponents = std::vector<RenderComponent*>();
	mDirectX = D3DApp::GetInstance();
	mGeometries = vector<MeshGeometry*>();
	Init();
}

RenderManager::~RenderManager()
{
	for(auto geo : mGeometries)
		delete geo;
	mGeometries.clear();

	for (auto comp : mComponents)
		delete comp;
	mComponents.clear();
}

void RenderManager::Init()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(80.0F), (float)mDirectX->GetAspectRatio(), 0.05F, 1000.0F));

	CreateGeometries();
	CreateShaders();
}

void RenderManager::CreateGeometries()
{
	Vertex1 losVertices[] = {
	   { XMFLOAT3(0.0f, 3.0f, 0.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
	   { XMFLOAT3(1.0f, 0.0f, 1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
	   { XMFLOAT3(1.0f, 0.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
	   { XMFLOAT3(-1.0f, 0.0f, -1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
	   { XMFLOAT3(-1.0f, 0.0f, 1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
	   { XMFLOAT3(0.0f, -3.0f, 0.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }
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


	Vertex1 quadVertices[] = {
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f,1.0f) },

		{ XMFLOAT3(1.0f, 1.0f, 0.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f,1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0.0f,0.0f) }
	};
	std::uint16_t quadIndices[] = {
		0,1,2,3,4,5
	};

	mGeometries.push_back(CreateGeometry(quadVertices, _countof(quadVertices), quadIndices, _countof(quadIndices), "Quad"));


	/*Vertex1 cubeVertices[] = {
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 0
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 1
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 2
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 3
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 4
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 5
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 6
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) } 7
	};*/

	Vertex1 cubeVertices[] = {
		//Front face
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//back Face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },

		//left face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//right face
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//top face
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//bottom face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(1,1) }
	};

	std::uint16_t cubeIndices[_countof(cubeVertices)];

	for (int i = 0; i < _countof(cubeVertices);i++)
	{
		cubeIndices[i] = i;
	}

	mGeometries.push_back(CreateGeometry(cubeVertices, _countof(cubeVertices), cubeIndices, _countof(cubeIndices), "Cube"));
}

XMFLOAT2 RenderManager::CalculateUV(XMFLOAT3 xyz)
{
	return XMFLOAT2(1.0f, 1.0f);
}

void RenderManager::CreateShaders()
{
	TextureShader* textShad = new TextureShader();
	mDirectX->CreateShader(textShad, L"Shaders\\Hlsl\\TextureShader.hlsl");
	mShaders.push_back(textShad);

	ShaderBasic* shadbase = new ShaderBasic();
	mDirectX->CreateShader(shadbase, L"Shaders\\Hlsl\\BaseShader.hlsl");
	mShaders.push_back(shadbase);
}


void RenderManager::ResetShaders()
{
	for (int i = 0; i < mShaders.size(); i++)
	{
		mShaders[i]->Reset();
	}
}

MeshGeometry* RenderManager::GetLosangeMesh() { return mGeometries[0]; }

MeshGeometry* RenderManager::GetSquareMesh() { return mGeometries[1]; }

MeshGeometry* RenderManager::GetCubeMesh() { return mGeometries[2]; }

Shader* RenderManager::GetShaderById(int index) { return mShaders[index]; }

Texture* RenderManager::CreateTexture(string name, const wchar_t* path, int* textureOffset) {
	*textureOffset = mTextureCount;
	mTextureCount++;
	return mDirectX->CreateTexture(name, path, *textureOffset);
}

MeshGeometry* RenderManager::CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

void RenderManager::Render() 
{
	XMFLOAT4X4 viewProj;
	XMStoreFloat4x4(&viewProj, XMMatrixTranspose(GameObjectManager::GetInstance()->GetCamera()->GetView() * XMLoadFloat4x4(&mProjMatrix)));

	for (int i = 0; i < mShaders.size(); i++)
	{
		mShaders[i]->SetPassCB(viewProj);
		mShaders[i]->UpdatePass();
	}
}