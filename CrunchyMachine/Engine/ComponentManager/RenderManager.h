#pragma once
#include "EngineResources/framework.h"
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/RenderComponent.h"
#include <vector>

class D3DApp;
class MeshGeometry;
class GameObject;
class Shader;

// Manages the rendering process between game object's component and DirectX12 render pipeline.
// It also stores pre-builded geometries and shaders.
// Providing functions to create own geometries and textures, but it doesn't store them.
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
	~RenderManager() override;
	
	MeshGeometry* CreateGeometry(Vertex vertex[], int numVer, uint16_t index[], int numInd, string name) const;
	Texture* CreateTexture(string name, const wchar_t* path, int* textureOffset, bool cubeMap = false);
	
	virtual void Update(float deltaTime) override;
	void Render() const;
	
	static float GetAspectRatio();
	static int GetClientWidth();
	static int GetClientHeight();

	MeshGeometry* GetLosMesh() const;
	MeshGeometry* GetSquareMesh() const;
	MeshGeometry* GetCubeMesh() const;
	MeshGeometry* GetSphereMesh() const;
	MeshGeometry GetSkyMesh() const;

	Shader* GetShader(SHAD index) const;
	Shader* GetSkyShader() const;
	
	void ResetShaders() const;
};