#pragma once
#include "Resources/framework.h"
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/RenderComponent.h"

class D3DApp;
class MeshGeometry;
class GameObject;
class RenderComponent;

class RenderManager : public ComponentManager<RenderComponent>
{
	D3DApp* mDirectX;

	vector<MeshGeometry*> geometries;


	void Init();

public:

	RenderManager();
	~RenderManager();

	MeshGeometry* GetLosangeMesh();
	MeshGeometry* GetSquareMesh();
	MeshGeometry* GetCubeMesh();

	MeshGeometry* CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name);
	RenderComponent* CreateRenderComponent(MeshGeometry* geo);

	void Render();
};

