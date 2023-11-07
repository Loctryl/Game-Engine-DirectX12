#include "Box.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include <random>

Box::Box() : GameObject()
{

}

void Box::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	comp->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* physics = new PhysicsComponent(mTransform, true, 2);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	int randomsize = 10000;
	mTransform->Translate((float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100);
}

void Box::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void Box::OnDestroy()
{
}

void Box::OnCollision(GameObject* gt)
{
}
