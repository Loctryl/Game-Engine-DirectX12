#pragma once
#include "Engine/GameObject.h"

class Camera;

// Planets manager, making them spawn
class PlanetCreator : public GameObject
{
	int mPlanetNumber = 5;
	Camera* mCamera;
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;
	
	void SetPlanet(int index);
	void SetUpPlanets();

public:
	PlanetCreator();
	~PlanetCreator() override;
};

