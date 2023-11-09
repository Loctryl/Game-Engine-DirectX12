#include "PlanetCreator.h"
#include "Planet.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Resources/framework.h"
#include <random>

PlanetCreator::PlanetCreator() : GameObject()
{
	mCamera = GameObjectManager::GetInstance()->GetCamera();
}


void PlanetCreator::SetPlanet(int indice)
{
	int maxScale = 75;
	int minScale = 35;
	float scale = rand() % (maxScale - minScale + 1) + maxScale;

	int xmax = 1000;
	int xmin = BORDER_SIZE + scale;
	float xPos = rand() % (xmax - xmin + 1) + xmin;
	if (rand() % 2 == 1) xPos *= -1;

	int zmax = 1000;
	float zPos = rand() % zmax;

	int ymax = 500;
	float yPos = rand() % ymax;
	if (rand() % 2 == 1) yPos *= -1;

	XMFLOAT3 position = XMFLOAT3(xPos, yPos, zPos);
	XMVECTOR pos = XMLoadFloat3(&position);

	Planet* planet = new Planet(indice, position, scale);
	mPlanets[indice] = planet;
	cout << position.x << " , " << position.y << " , " << position.z << endl;
}

void PlanetCreator::SetUpPlanets()
{
	for (int i = 0; i < 5; i++) {
		SetPlanet(i);
	}
}

void PlanetCreator::OnInit()
{
	mTransform->SetPosition(mCamera->mTransform->GetWorldPosition());
	SetUpPlanets();
}

void  PlanetCreator::OnUpdate(float deltaTime)
{
	mTransform->SetPosition(mCamera->mTransform->GetWorldPosition());
}

void  PlanetCreator::OnDestroy()
{
	
}

void  PlanetCreator::OnCollision(GameObject* gt)
{

}