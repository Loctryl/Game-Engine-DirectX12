#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	//RenderComponent* comp = new RenderComponent(SPHERE, 1);
	//AddComponent<RenderComponent>(comp);
	PhysicsComponent* phy = new PhysicsComponent(mTransform, true, 1);
	AddComponent<PhysicsComponent>(phy);

	mTransform->SetPosition(0.0f,0.0f,0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{

}

void SpaceShip::OnDestroy()
{
	delete mTransform;
}

void SpaceShip::OnCollision(GameObject* gt)
{
}
