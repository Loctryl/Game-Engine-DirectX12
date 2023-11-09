#pragma once
#include "Engine/GameObject.h"

// Environment 
class Planet : public GameObject
{
public:
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

	Planet(int texIndex, XMFLOAT3 position, float scale);
	~Planet() override = default;

private: 
	const wchar_t* mTextures[5]{
	L"Resources\\Assets\\PlanetTex1.dds",
	L"Resources\\Assets\\PlanetTex2.dds",
	L"Resources\\Assets\\PlanetTex3.dds",
	L"Resources\\Assets\\PlanetTex4.dds",
	L"Resources\\Assets\\PlanetTex5.dds"
	};
};
