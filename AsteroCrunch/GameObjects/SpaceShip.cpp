#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include <random>

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, 3, L"Resources\\Assets\\box.dds", "Yes"));
	PhysicsComponent* physics = new PhysicsComponent(mTransform, true, 2);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	int randomsize = 50;
	mTransform->Translate((float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	//mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void SpaceShip::OnDestroy() { RELPTR(mTransform); }

void SpaceShip::OnCollision(GameObject* gt)
{
}
