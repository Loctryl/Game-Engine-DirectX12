#include "Rocket.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Input.h"
#include "EngineResources/Color.h"
#include "Resources/framework.h"


Rocket::Rocket(GameObject* SpaceShip) : GameObject()
{
	mId->SetMask(ALLY_ROCKET);
}

Rocket::~Rocket()
{
}

void Rocket::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	comp->SetColor(Color::red());
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* physic = new PhysicsComponent(mTransform, false, 1);
	physic->SetMask(ALLY_ROCKET);
	physic->SetMask(ASTERO);
	physic->SetMask(ENEMIE_ROCKET);

	AddComponent<PhysicsComponent>(physic);
	mTransform->SetScale(.5f, .5f, 2);
	
	XMFLOAT3 something = mTransform->GetDirz();
	XMVECTOR tempTranslate = XMLoadFloat3(&something) * mSpeed;
	XMFLOAT3 translate;
	XMStoreFloat3(&translate, tempTranslate);

	physic->AddVelocity(translate);
}

void Rocket::OnUpdate(float deltaTime)
{
}

void Rocket::OnDestroy()
{
}

void Rocket::OnCollision(GameObject* gt)
{
	ToDestroy = true;
}