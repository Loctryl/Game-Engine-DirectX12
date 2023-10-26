#pragma once
#include "Resources/framework.h"
#include <vector>

class D3DApp;
class MeshGeometry;
class GameObject;
class RenderComponent;

class GeoManager
{
	static GeoManager* mInstance;

	D3DApp* mDirectX;

	vector<MeshGeometry*> geometries;


	void Init();

public:
	vector<GameObject*> gObj;


	GeoManager();
	GeoManager(D3DApp* mDApp);
	~GeoManager();

	static GeoManager* GetInstance();

	MeshGeometry* GetLosangeMesh();
	MeshGeometry* GetSquareMesh();
	MeshGeometry* GetCubeMesh();

	MeshGeometry* CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name);
	RenderComponent* CreateRenderComponent(MeshGeometry* geo);

	void Render();
};

