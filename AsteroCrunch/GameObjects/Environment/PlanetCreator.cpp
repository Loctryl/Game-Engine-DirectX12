#include "PlanetCreator.h"
#include "Planet.h"
#include "Engine/Component/Transform.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Resources/framework.h"
#include <random>

PlanetCreator::PlanetCreator() : GameObject()
{
	mCamera = GameObjectManager::GetInstance()->GetCamera();
}

PlanetCreator::~PlanetCreator() { mCamera = nullptr; }

void PlanetCreator::OnInit()
{
	mTransform->SetPosition(mCamera->mTransform->GetWorldPosition());
	SetUpPlanets();
}

void  PlanetCreator::OnUpdate(float deltaTime) { mTransform->SetPosition(mCamera->mTransform->GetWorldPosition()); }

void  PlanetCreator::OnDestroy() { }

void  PlanetCreator::OnCollision(GameObject* go) { }

// Making a planet spawn randomly around the player
void PlanetCreator::SetPlanet(int index)
{
	int maxScale = 125;
	int minScale = 50;
	float scale = rand() % (maxScale - minScale + 1) + maxScale;

	int xmax = 1000;
	int xmin = BORDER_SIZE + scale;
	float xPos = rand() % (xmax - xmin + 1) + xmin;
	if (rand() % 2 == 1) xPos *= -1;

	int zmax = 2000;
	float zPos = rand() % zmax;

	int ymax = 500;
	float yPos = rand() % ymax;
	if (rand() % 2 == 1) yPos *= -1;

	XMFLOAT3 position = XMFLOAT3(xPos, yPos, zPos);
	XMVECTOR pos = XMLoadFloat3(&position);

	Planet* planet = new Planet(index, position, scale);
}

void PlanetCreator::SetUpPlanets()
{
	for (int i = 0; i < mPlanetNumber; i++) 
		SetPlanet(i);
}