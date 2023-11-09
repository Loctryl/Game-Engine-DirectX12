#pragma once
#include "Engine/GameObject.h"

class Planet : public GameObject
{
public:
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	Planet(int texIndice, XMFLOAT3 position, float scale);
	~Planet();

private: 
	const wchar_t* mTextures[5]{
	L"Resources\\Assets\\PlanetTex1.dds",
	L"Resources\\Assets\\PlanetTex2.dds",
	L"Resources\\Assets\\PlanetTex3.dds",
	L"Resources\\Assets\\PlanetTex4.dds",
	L"Resources\\Assets\\PlanetTex5.dds"
	};
};
