#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, 1));
	PhysicsComponent* physics = new PhysicsComponent(mTransform, true, 2);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	mTransform->SetPosition(2.5f,2.0f,0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void SpaceShip::OnDestroy() { RELPTR(mTransform); }

void SpaceShip::OnCollision(GameObject* gt)
{
}
