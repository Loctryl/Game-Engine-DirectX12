#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(CUBE, 2);
	AddComponent<RenderComponent>(comp);

	mTransform->SetPosition(2.5f,2.0f,0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void SpaceShip::OnDestroy()
{
	delete mTransform;
}