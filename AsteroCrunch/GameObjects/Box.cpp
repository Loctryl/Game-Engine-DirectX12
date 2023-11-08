#include "Box.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include <random>
#include "GameObjects/SpaceShip/SpaceShipPart.h"

Box::Box() : GameObject()
{
	mParts[0] = new SpaceShipPart();
	mParts[1] = new SpaceShipPart();
	mParts[2] = new SpaceShipPart();
	mParts[3] = new SpaceShipPart();
	mParts[4] = new SpaceShipPart();
	mParts[0]->AddParent(this);
	mParts[1]->AddParent(this);
	mParts[2]->AddParent(this);
	mParts[3]->AddParent(this);
	mParts[4]->AddParent(this);

	RenderComponent* cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[0]->AddComponent<RenderComponent>(cube);
	mParts[0]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	mParts[0]->mTransform->SetScale(1.2f, 0.1f, 0.2f);

	cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[1]->AddComponent<RenderComponent>(cube);
	mParts[1]->mTransform->SetPosition(1.2f, 0.0f, 0.0f);
	mParts[1]->mTransform->SetScale(0.05f, 1.0f, 1.2f);

	cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[2]->AddComponent<RenderComponent>(cube);
	mParts[2]->mTransform->SetPosition(-1.2f, 0.0f, 0.0f);
	mParts[2]->mTransform->SetScale(0.05f, 1.4f, 1.0f);

	cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[3]->AddComponent<RenderComponent>(cube);
	mParts[3]->mTransform->SetPosition(1.2f, 0.0f, 0.0f);
	mParts[3]->mTransform->SetScale(0.05f, 1.4f, 1.0f);

	cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[4]->AddComponent<RenderComponent>(cube);
	mParts[4]->mTransform->SetPosition(-1.2f, 0.0f, 0.0f);
	mParts[4]->mTransform->SetScale(0.05f, 1.0f, 1.2f);
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
