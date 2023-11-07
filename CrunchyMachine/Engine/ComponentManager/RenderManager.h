#pragma once
#include "EngineResources/framework.h"
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/RenderComponent.h"

class D3DApp;
class MeshGeometry;
class GameObject;
class Shader;

// Manages the rendering process between game object's component and DirectX12 render pipeline.
// It also stores prebuilded geometries and shaders.
// Providing fonctions to create own geometries and textures, but it doesn't store them.
class RenderManager : public ComponentManager<RenderComponent>
{
private:
	D3DApp* mDirectX;

	vector<MeshGeometry*> mGeometries;

	vector<Shader*> mShaders;

	int mTextureCount = 0;

	void Init();
	XMFLOAT3 ComputeNormal(XMFLOAT3 p0, XMFLOAT3 p1, XMFLOAT3 p2);
	void CreateGeometries();
	void CreateShaders();

public:
	RenderManager();
	~RenderManager();

	void Update(float deltaTime);

	MeshGeometry* GetLosangeMesh();
	MeshGeometry* GetSquareMesh();
	MeshGeometry* GetScoreMesh();
	MeshGeometry* GetCubeMesh();
	MeshGeometry* GetSphereMesh();
	MeshGeometry GetSkyMesh();

	Shader* GetShader(SHAD index);
	Shader* GetSkyShader();

	static float GetAspectRatio();

	void ResetShaders();

	MeshGeometry* CreateGeometry(Vertex vertex[], int numVer, uint16_t index[], int numInd, string name);
	Texture* CreateTexture(string name, const wchar_t* path, int* textureOffset, bool cubeMap = false);

	void Render();
};