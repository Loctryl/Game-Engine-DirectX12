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
}

void RenderManager::Init()
{
	XMStoreFloat4x4(&mProjMatrix, XMMatrixPerspectiveFovLH(XMConvertToRadians(80.0F), (float)mDirectX->GetAspectRatio(), 0.05F, 1000.0F));

	CreateGeometries();
	CreateShaders();

}

void RenderManager::CreateGeometries()
{
	Vertex1 losVertices[] =
	{
	   { XMFLOAT3(0.0f, 3.0f, 0.0f), Color::white()},
	   { XMFLOAT3(1.0f, 0.0f, 1.0f), Color::cyan()},
	   { XMFLOAT3(1.0f, 0.0f, -1.0f), Color::red()},
	   { XMFLOAT3(-1.0f, 0.0f, -1.0f), Color::purple() },
	   { XMFLOAT3(-1.0f, 0.0f, 1.0f), Color::green() },
	   { XMFLOAT3(0.0f, -3.0f, 0.0f), Color::black() }
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
	   { XMFLOAT3(1.0f, 1.0f, 0.0f), Color::cyan()},
	   { XMFLOAT3(1.0f, -1.0f, 0.0f), Color::red()},
	   { XMFLOAT3(-1.0f, -1.0f, 0.0f), Color::purple() },
	   { XMFLOAT3(-1.0f, 1.0f, 0.0f), Color::green() }
	};

	std::uint16_t quadIndices[] = {
		0,1,2,
		0,1,2,
		0,2,3
	};

	mGeometries.push_back(CreateGeometry(quadVertices, _countof(quadVertices), quadIndices, _countof(quadIndices), "Quad"));


	Vertex1 cubeVertices[] =
	{
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black() },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan() },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red() },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green() },
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple() },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue() },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white() },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow() }
	};

	std::uint16_t cubeIndices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,
		// back face
		4, 6, 5,
		4, 7, 6,
		// left face
		4, 5, 1,
		4, 1, 0,
		// right face
		3, 2, 6,
		3, 6, 7,
		// top face
		1, 5, 6,
		1, 6, 2,
		// bottom face
		4, 0, 3,
		4, 3, 7
	};

	mGeometries.push_back(CreateGeometry(cubeVertices, _countof(cubeVertices), cubeIndices, _countof(cubeIndices), "Cube"));

	XMFLOAT3 size = { 1,1,1 };

	int phiCount = 6;
	int thetaCount = 6;

	float thetaStep = XM_PI / thetaCount;
	float phiStep = XM_2PI / phiCount;

	const int numVertices = 2 + phiCount * (thetaCount - 1);
	const int numIndices = (2 * 3 * phiCount + 2 * 3 * phiCount * (thetaCount - 2));

	Vertex1* sphereVertices = new Vertex1[numVertices];

	int c = 0;

	sphereVertices[c++] = {XMFLOAT3( 0.f, size.y, 0.f ), Color::red()};

	for (int j = 1; j <= (thetaCount - 1); j++) {
		float theta = j * thetaStep;

		for (int i = 0; i < phiCount; i++) {
			int phi = i * phiStep;

			XMFLOAT4 color;
			if (i % 2 == 0) color = Color::blue();
			else color = Color::green();

			Vertex1 vert = {
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
		for (int i = 0; i < (phiCount -1); i++) {
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
	int southPoleIndex = numVertices -1;

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
	mDirectX->CreateShader(shadbase, L"Shaders\\Hlsl\\BaseShader.hlsl");
	mShaders.push_back(shadbase);

	ShaderTEST* shad = new ShaderTEST();
	mDirectX->CreateShader(shad, L"Shaders\\Hlsl\\RedBaseShader.hlsl");
	mShaders.push_back(shad);
}


void RenderManager::ResetShaders()
{
	for (int i = 0; i < mShaders.size(); i++)
	{
		mShaders[i]->Reset();
	}
}

MeshGeometry* RenderManager::GetLosangeMesh()
{
	return mGeometries[0];
}

MeshGeometry* RenderManager::GetSquareMesh()
{
	return mGeometries[1];
}

MeshGeometry* RenderManager::GetCubeMesh()
{
	return mGeometries[2];
}

MeshGeometry* RenderManager::GetSphereMesh()
{
	return mGeometries[3];
}

Shader* RenderManager::GetShaderById(int index)
{
	return mShaders[index];
}

MeshGeometry* RenderManager::CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

RenderComponent* RenderManager::CreateRenderComponent(MeshGeometry* geo, Shader* shad)
{
	return mDirectX->CreateRenderComponent(geo, shad);
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