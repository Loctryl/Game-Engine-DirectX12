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
	RenderComponent* comp = new RenderComponent(SPHERE, LITTEXTURE, L"Resources//Assets//asteroTex2.dds");
	comp->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* physics = new PhysicsComponent(mTransform, true, 100);
	AddComponent<PhysicsComponent>(physics);
	mTransform->SetScale(100);
	mTransform->SetPosition(-300,0, 300);
}

void Box::OnUpdate(float deltaTime)
{
	//mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void Box::OnDestroy()
{
}

void Box::OnCollision(GameObject* gt)
{
}
