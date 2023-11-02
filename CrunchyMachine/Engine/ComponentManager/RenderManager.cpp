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
	for (auto geo : mGeometries)
		RELPTR(geo);
	mGeometries.clear();

	for (auto comp : mComponents)
		RELPTR(comp);
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
	Vertex losVertices[] = {
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


	Vertex quadVertices[] = {
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

	Vertex cubeVertices[] = {
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

	for (int i = 0; i < _countof(cubeVertices); i++)
	{
		cubeIndices[i] = i;
	}

	mGeometries.push_back(CreateGeometry(cubeVertices, _countof(cubeVertices), cubeIndices, _countof(cubeIndices), "Cube"));


	// Creates a sphere mesh
	XMFLOAT3 size = { 1,1,1 };

	int phiCount = 25;
	int thetaCount = 25;

	float thetaStep = XM_PI / thetaCount;
	float phiStep = XM_2PI / phiCount;

	const int numVertices = 2 + phiCount * (thetaCount - 1);
	const int numIndices = (2 * 3 * phiCount + 2 * 3 * phiCount * (thetaCount - 2));

	Vertex* sphereVertices = new Vertex[numVertices];

	int c = 0;

	sphereVertices[c++] = { XMFLOAT3(0.f, size.y, 0.f), Color::red() };

	for (int j = 1; j <= (thetaCount - 1); j++) {
		float theta = j * thetaStep;

		//XMFLOAT4 color = XMFLOAT4(0.5, 0.5, 0.5, 1.0f

		for (int i = 0; i < phiCount; i++) {
			float phi = i * phiStep;

			XMFLOAT4 color;
			if (i % 2 == 0) color = Color::cyan();
			else color = Color::red();

			Vertex vert = {
				XMFLOAT3(
					size.x * XMScalarSin(theta) * XMScalarCos(phi),
					size.y * XMScalarCos(theta),
					-size.z * XMScalarSin(theta) * XMScalarSin(phi)
				),
				color
			};
			sphereVertices[c++] = vert;
		}
	}

	sphereVertices[c++] = { XMFLOAT3(0.f, -size.y, 0.f), Color::red() };
	assert(c == numVertices);

	c = 0;


	std::uint16_t* rawSphereIndices = new std::uint16_t[numIndices];

	//Indices for the top cap 
	for (int i = 0; i < phiCount - 1; i++) {
		rawSphereIndices[c++] = 0;
		rawSphereIndices[c++] = i + 1;
		rawSphereIndices[c++] = i + 2;
	}

	rawSphereIndices[c++] = 0;
	rawSphereIndices[c++] = phiCount;
	rawSphereIndices[c++] = 1;

	//Indices for the section between the top and bottom rings
	for (int j = 0; j < (thetaCount - 2); j++) {
		for (int i = 0; i < (phiCount - 1); i++) {
			int index[4]{
				1 + i + j * phiCount,
				1 + i + (j + 1) * phiCount,
				1 + (i + 1) + (j + 1) * phiCount,
				1 + (i + 1) + j * phiCount
			};

			rawSphereIndices[c++] = index[0];
			rawSphereIndices[c++] = index[1];
			rawSphereIndices[c++] = index[2];

			rawSphereIndices[c++] = index[0];
			rawSphereIndices[c++] = index[2];
			rawSphereIndices[c++] = index[3];
		}

		int index[4]{
			phiCount + j * phiCount,
			phiCount + (j + 1) * phiCount,
			1 + (j + 1) * phiCount,
			1 + j * phiCount
		};

		rawSphereIndices[c++] = index[0];
		rawSphereIndices[c++] = index[1];
		rawSphereIndices[c++] = index[2];

		rawSphereIndices[c++] = index[0];
		rawSphereIndices[c++] = index[2];
		rawSphereIndices[c++] = index[3];
	}

	//indices for the bottom cap
	int southPoleIndex = numVertices - 1;

	for (int i = 0; i < phiCount - 1; i++) {
		rawSphereIndices[c++] = southPoleIndex;
		rawSphereIndices[c++] = southPoleIndex - phiCount + i + 1;
		rawSphereIndices[c++] = southPoleIndex - phiCount + i;
	}

	rawSphereIndices[c++] = southPoleIndex;
	rawSphereIndices[c++] = southPoleIndex - phiCount;
	rawSphereIndices[c++] = southPoleIndex - 1;
	mGeometries.push_back(CreateGeometry(sphereVertices, numVertices, rawSphereIndices, numIndices, "Sphere"));
}

void RenderManager::CreateShaders()
{

	//TextureShader* textShad = new TextureShader();
	//mInstance->mDirectX->CreateShader(textShad, L"Shaders\\Hlsl\\TextureShader.hlsl");
	//mShaders.push_back(textShad);

	ShaderBasic* shadbase = new ShaderBasic();
	mDirectX->CreateShader(shadbase, L"ShadersHlsl\\BaseShader.hlsl");
	mShaders.push_back(shadbase);

	ShaderTEST* shad = new ShaderTEST();
	mDirectX->CreateShader(shad, L"ShadersHlsl\\RedBaseShader.hlsl");
	mShaders.push_back(shad);
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

MeshGeometry* RenderManager::GetSphereMesh() { return mGeometries[3]; }

Shader* RenderManager::GetShaderById(int index) { return mShaders[index]; }

Texture* RenderManager::CreateTexture(string name, const wchar_t* path, int* textureOffset) {
	*textureOffset = mTextureCount;
	mTextureCount++;
	return mDirectX->CreateTexture(name, path, *textureOffset);
}

MeshGeometry* RenderManager::CreateGeometry(Vertex vertex[], int numVer, uint16_t index[], int numInd, string name)
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