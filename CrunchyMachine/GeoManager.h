#pragma once
#include "Resources/framework.h"
#include <vector>

class D3DApp;
class MeshGeometry;
class GameObject;
class RenderComponent;
class Shader;

class RenderManager
{
	static RenderManager* mInstance;

	D3DApp* mDirectX;

	XMFLOAT4X4 mProjMatrix;

	vector<MeshGeometry*> mGeometries;

	vector<Shader*> mShaders;

	void Init();
	void CreateGeometries();
	void CreateShaders();

public:
	vector<GameObject*> gObj;


	RenderManager();
	RenderManager(D3DApp* mDApp);
	~RenderManager();

	static RenderManager* GetInstance();

	MeshGeometry* GetLosangeMesh();
	MeshGeometry* GetSquareMesh();
	MeshGeometry* GetCubeMesh();

	Shader* GetShaderById(int index);

	MeshGeometry* CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name);
	RenderComponent* CreateRenderComponent(MeshGeometry* geo, Shader* shad);

	void Render();
};

