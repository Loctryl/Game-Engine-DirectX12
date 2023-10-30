#pragma once
#include "Resources/framework.h"
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/RenderComponent.h"

class D3DApp;
class MeshGeometry;
class GameObject;
class RenderComponent;
class Shader;

class RenderManager : public ComponentManager<RenderComponent>
{
	D3DApp* mDirectX;

	XMFLOAT4X4 mProjMatrix;

	vector<MeshGeometry*> mGeometries;

	vector<Shader*> mShaders;

	void Init();
	void CreateGeometries();
	void CreateShaders();

public:

	RenderManager();
	~RenderManager();

	void Update(float deltaTime);

	MeshGeometry* GetLosangeMesh();
	MeshGeometry* GetSquareMesh();
	MeshGeometry* GetCubeMesh();

	Shader* GetShaderById(int index);

	void ResetShaders();

	MeshGeometry* CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name);
	RenderComponent* CreateRenderComponent(MeshGeometry* geo, Shader* shad);

	void Render();
};

