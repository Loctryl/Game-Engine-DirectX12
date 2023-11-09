#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "EngineResources/Color.h"
#include "Resources/framework.h"
#include <random>

Astero::Astero(XMFLOAT3 position, XMFLOAT4 quat, float speed) : Entity()
{
	mTransform->SetPosition(position);
	mTransform->SetRotation(quat);
	mTransform->RotateOnAxis(0, 1, 0, 180); //make it face the player
	mSpeed = speed;

	mId->SetMask(ASTERO);
}

Astero::~Astero()
{
}

void Astero::OnInit()
{
	float scale = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_countof(mTextures) - 1)));

	AddComponent<RenderComponent>(new RenderComponent(SPHERE, LITTEXTURE, mTextures[(int)round(scale)]));
	scale++;
	InitMaxHp(round(scale)*2);
	scale = pow(scale, 2) * 3;

	physics = new PhysicsComponent(mTransform, true, scale);
	physics->SetMask(SPACESHIP);
	physics->SetMask(ASTERO);
	physics->SetMask(ALLY_ROCKET);
	physics->SetMask(ENEMY_ROCKET);
	AddComponent<PhysicsComponent>(physics);

	mTransform->SetScale(scale);
	XMFLOAT3 dirz = mTransform->GetDirz();
	XMVECTOR velocity = XMLoadFloat3(&dirz) * mSpeed;
	XMStoreFloat3(&dirz, velocity);
	physics->AddVelocity(dirz);
}

void Astero::OnUpdate(float deltaTime)
{

}

void Astero::OnDestroy()
{
}

void Astero::OnCollision(GameObject* go)
{

	if (!go->mId->IsBitMask(ASTERO)) {
		
		if (go->mId->IsBitMask(SPACESHIP)) {
			ToDestroy = true;
		}

		else {
			LoseHp(1);
		}
	}

}
