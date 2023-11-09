#pragma once
#include "Engine/GameObject.h"

class Camera;

class PlanetCreator : public GameObject
{ 
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	static const int mPlanetNumber = 10;
	GameObject* mPlanets[mPlanetNumber];
	Camera* mCamera;

	void SetPlanet(int indice);
	void SetUpPlanets();

public:

	PlanetCreator();
};

