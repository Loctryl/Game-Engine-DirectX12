#include "RenderManager.h"
#include "EngineResources/Color.h"
#include "DirectX12/D3DApp.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Shaders/TextureShader.h"
#include "Shaders/LitTextureShader.h"
#include "Shaders/LitShader.h"
#include "Shaders/SkyShader.h"
#include "Shaders/Shader.h"
#include "Engine/Component/Transform.h"

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
	CreateGeometries();
	CreateShaders();
}

XMFLOAT3 RenderManager::ComputeNormal(XMFLOAT3 p0, XMFLOAT3 p1, XMFLOAT3 p2)
{
	XMVECTOR u = XMLoadFloat3(&p1) - XMLoadFloat3(&p0);
	XMVECTOR v = XMLoadFloat3(&p2) - XMLoadFloat3(&p0);
	XMFLOAT3 n;
	XMStoreFloat3(&n, XMVector3Normalize(XMVector3Cross(u, v)));
	return n;
}

void RenderManager::CreateGeometries()
{
	//Vertex losVertices[] = {
	//	{ XMFLOAT3(0.0f, 3.0f, 0.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 0
	//	{ XMFLOAT3(1.0f, 0.0f, 1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 1
	//	{ XMFLOAT3(1.0f, 0.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 2
	//	{ XMFLOAT3(-1.0f, 0.0f, -1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 3
	//	{ XMFLOAT3(-1.0f, 0.0f, 1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) }, 4
	//	{ XMFLOAT3(0.0f, -3.0f, 0.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0,0) } 5
	//};

	XMFLOAT3 top = XMFLOAT3(0.0f, 3.0f, 0.0f);
	XMFLOAT3 bot = XMFLOAT3(0.0f, -3.0f, 0.0f);
	XMFLOAT3 X1Z1 = XMFLOAT3(1.0f, 0.0f, 1.0f);
	XMFLOAT3 X1Z = XMFLOAT3(1.0f, 0.0f, -1.0f);
	XMFLOAT3 XZ1 = XMFLOAT3(-1.0f, 0.0f, 1.0f);
	XMFLOAT3 XZ = XMFLOAT3(-1.0f, 0.0f, -1.0f);

	XMFLOAT3 n1 = ComputeNormal(top, X1Z1, X1Z);
	XMFLOAT3 n2 = ComputeNormal(top, X1Z, XZ);
	XMFLOAT3 n3 = ComputeNormal(top, XZ, XZ1);
	XMFLOAT3 n4 = ComputeNormal(top, XZ1, X1Z1);

	XMFLOAT3 n5 = ComputeNormal(bot, X1Z, X1Z1);
	XMFLOAT3 n6 = ComputeNormal(bot, XZ, X1Z);
	XMFLOAT3 n7 = ComputeNormal(bot, XZ1, XZ);
	XMFLOAT3 n8 = ComputeNormal(bot, X1Z1, XZ1);


	Vertex losVertices[] = {
		{ top, Color::white(), n1, XMFLOAT2(0.5f,0) },
		{ X1Z1, Color::cyan(), n1, XMFLOAT2(1,1) },
		{ X1Z, Color::red(), n1, XMFLOAT2(0,1) },

		{ top, Color::white(), n2, XMFLOAT2(0.5f,0) },
		{ X1Z, Color::red(), n2, XMFLOAT2(1,1) },
		{ XZ, Color::purple(), n2, XMFLOAT2(0,1) },

		{ top, Color::white(), n3, XMFLOAT2(0.5f,0) },
		{ XZ, Color::purple(), n3, XMFLOAT2(1,1) },
		{ XZ1, Color::green(), n3, XMFLOAT2(0,1) },

		{ top, Color::white(), n4, XMFLOAT2(0.5f,0) },
		{ XZ1, Color::green(), n4, XMFLOAT2(1,1) },
		{ X1Z1, Color::cyan(), n4, XMFLOAT2(0,1) },


		{ bot, Color::black(), n5, XMFLOAT2(0.5f,1) },
		{ X1Z, Color::red(), n5, XMFLOAT2(0,0) },
		{ X1Z1, Color::cyan(), n5, XMFLOAT2(1,0) },

		{ bot, Color::black(), n6, XMFLOAT2(0.5f,1) },
		{ XZ, Color::purple(), n6, XMFLOAT2(0,0) },
		{ X1Z, Color::red(), n6, XMFLOAT2(1,0) },

		{ bot, Color::black(), n7, XMFLOAT2(0.5f,1) },
		{ XZ1, Color::green(), n7, XMFLOAT2(0,0) },
		{ XZ, Color::purple(), n7, XMFLOAT2(1,0) },

		{ bot, Color::black(), n8, XMFLOAT2(0.5f,1) },
		{ X1Z1, Color::cyan(), n8, XMFLOAT2(0,0) },
		{ XZ1, Color::green(), n8, XMFLOAT2(1,0) },
	};


	std::uint16_t losIndices[_countof(losVertices)];

	for (int i = 0; i < _countof(losVertices); i++)
		losIndices[i] = i;

	mGeometries.push_back(CreateGeometry(losVertices, _countof(losVertices), losIndices, _countof(losIndices), "Losange"));
	mGeometries[0]->mBVolume = new BoundingBox(XMFLOAT3(2.f, 4.f, 2.0f));



	Vertex quadVertices[] = {
		{ XMFLOAT3(1.0f, 1.0f, 0.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 0.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f,1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f,1.0f) },

		{ XMFLOAT3(1.0f, 1.0f, 0.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f,0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 0.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f,1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 0.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f,0.0f) }
	};
	std::uint16_t quadIndices[] = {
		0,1,2,3,4,5
	};

	mGeometries.push_back(CreateGeometry(quadVertices, _countof(quadVertices), quadIndices, _countof(quadIndices), "Quad"));
	mGeometries[1]->mBVolume = new BoundingBox(XMFLOAT3(2.f, 2.f, 0.5f));


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
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1,1) },

		//back Face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f,1.0f), XMFLOAT2(1,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1,1) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0,0) },

		//left face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//right face
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1,1) },

		//top face
		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, +1.0f, +1.0f), Color::blue(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, +1.0f, -1.0f), Color::cyan(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, +1.0f, +1.0f), Color::white(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, +1.0f, -1.0f), Color::red(), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1,1) },

		//bottom face
		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), Color::black(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0,0) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1,0) },

		{ XMFLOAT3(-1.0f, -1.0f, +1.0f), Color::purple(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0,1) },
		{ XMFLOAT3(+1.0f, -1.0f, -1.0f), Color::green(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1,0) },
		{ XMFLOAT3(+1.0f, -1.0f, +1.0f), Color::yellow(), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1,1) }
	};

	std::uint16_t cubeIndices[_countof(cubeVertices)];

	for (int i = 0; i < _countof(cubeVertices); i++)
		cubeIndices[i] = i;

	mGeometries.push_back(CreateGeometry(cubeVertices, _countof(cubeVertices), cubeIndices, _countof(cubeIndices), "Cube"));
	mGeometries[2]->mBVolume = new BoundingBox();


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

			XMFLOAT4 color = {0.5f,0.5f,0.5f,1.0f};
			/*if (i % 2 == 0) color = Color::cyan();
			else color = Color::red();*/

			Vertex vert;
			vert.Pos = XMFLOAT3(
				size.x * XMScalarSin(theta) * XMScalarCos(phi),
				size.y * XMScalarCos(theta),
				-size.z * XMScalarSin(theta) * XMScalarSin(phi)
			);
			vert.Color = color;

			XMVECTOR p = XMLoadFloat3(&vert.Pos);
			XMStoreFloat3(&vert.Normal, XMVector3Normalize(p));
				
			vert.TexCoord =	XMFLOAT2(theta / XM_2PI, phi / XM_PI);
			
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
	mGeometries[3]->mBVolume = new BoundingSphere();

}

void RenderManager::CreateShaders()
{
	ColorShader* colorShad = new ColorShader();
	mDirectX->CreateShader(colorShad, L"ShadersHlsl\\ColorShader.hlsl");
	mShaders.push_back(colorShad);

	TextureShader* textShad = new TextureShader();
	mDirectX->CreateShader(textShad, L"ShadersHlsl\\TextureShader.hlsl");
	mShaders.push_back(textShad);

	LitShader* litShad = new LitShader();
	mDirectX->CreateShader(litShad, L"ShadersHlsl\\LitShader.hlsl");
	mShaders.push_back(litShad);

	LitTextureShader* litTexShad = new LitTextureShader();
	mDirectX->CreateShader(litTexShad, L"ShadersHlsl\\LitTextureShader.hlsl");
	mShaders.push_back(litTexShad);

	SkyShader* skyShad = new SkyShader();
	mDirectX->CreateShader(skyShad, L"ShadersHlsl\\SkyShader.hlsl", false);
	mShaders.push_back(skyShad);
}

void RenderManager::Update(float deltaTime)
{
	for (auto obj : mComponents) {

	XMFLOAT3 cam = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetPosition();

	XMFLOAT3 Pos = obj->mGameObject->mTransform->GetPosition();

	//do not test collision if the object is too far away of the camera
	if (std::abs(Pos.x - cam.x) > KILLBOX ||
		std::abs(Pos.y - cam.y) > KILLBOX ||
		std::abs(Pos.z - cam.z) > KILLBOX
		)
		obj->mGameObject->ToDestroy = true;
	}
}

void RenderManager::ResetShaders()
{
	for (int i = 0; i < mShaders.size(); i++)
		mShaders[i]->Reset();
}

MeshGeometry* RenderManager::GetLosangeMesh() { return mGeometries[0]; }

MeshGeometry* RenderManager::GetSquareMesh() { return mGeometries[1]; }

MeshGeometry* RenderManager::GetCubeMesh() { return mGeometries[2]; }

MeshGeometry* RenderManager::GetSphereMesh() { return mGeometries[3]; }

MeshGeometry RenderManager::GetSkyMesh() { return *mGeometries[3]; }


Shader* RenderManager::GetShaderById(int index) { return mShaders[index]; }

Shader* RenderManager::GetSkyShader() { return mShaders.back(); }


float RenderManager::GetAspectRatio() { return D3DApp::GetInstance()->GetAspectRatio(); }

Texture* RenderManager::CreateTexture(string name, const wchar_t* path, int* textureOffset, bool cubeMap) {
	mDirectX->mCbvHeap->GetCPUDescriptorHandleForHeapStart();
	*textureOffset = mTextureCount;
	mTextureCount++;
	return mDirectX->CreateTexture(name, path, *textureOffset, cubeMap);
}

MeshGeometry* RenderManager::CreateGeometry(Vertex vertex[], int numVer, uint16_t index[], int numInd, string name)
{
	return mDirectX->CreateGeometry(vertex, numVer, index, numInd, name);
}

void RenderManager::Render()
{
	for (int i = 0; i < mShaders.size(); i++)
	{
		mShaders[i]->SetPassCB();
		mShaders[i]->UpdatePass();
	}
}