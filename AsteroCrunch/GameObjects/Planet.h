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
	L"Resources//Assets//PlanetTex//PlanetTex1.dds",
	L"Resources//Assets//PlanetTex//PlanetTex2.dds",
	L"Resources//Assets//PlanetTex//PlanetTex3.dds",
	L"Resources//Assets//PlanetTex//PlanetTex4.dds",
	L"Resources//Assets//PlanetTex//PlanetTex5.dds",
	/*L"Resources//Assets//PlanetTex//PlanetTex6.dds",
	L"Resources//Assets//PlanetTex//PlanetTex7.dds",
	L"Resources//Assets//PlanetTex//PlanetTex8.dds",
	L"Resources//Assets//PlanetTex//PlanetTex9.dds",
	L"Resources//Assets//PlanetTex//PlanetTex10.dds"*/
	};
};
