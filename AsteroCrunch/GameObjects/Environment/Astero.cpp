#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Engine.h"
#include "Resources/framework.h"
#include "UI/Score.h"
#include <random>

Astero::Astero(XMFLOAT3 position, XMFLOAT4 quat, float speed) : Entity()
{
	mTransform->SetPosition(position);
	mTransform->SetRotation(quat);
	mTransform->RotateOnAxis(0, 1, 0, 180); //make it face the player
	mSpeed = speed;

	mPhysic = nullptr;

	mId->SetMask(ASTERO);
}

Astero::~Astero() { mPhysic = nullptr; }

void Astero::OnInit()
{
	float scale = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_countof(mTextures) - 1)));

	AddComponent<RenderComponent>(new RenderComponent(SPHERE, LIT_TEXTURE, mTextures[(int)round(scale)]));
	scale++;
	mScoreValue = 100 * scale;
	InitMaxHp(round(scale)*2);
	scale = pow(scale, 2) * 3;

	mPhysic = new PhysicsComponent(mTransform, true, scale);
	mPhysic->SetMask(SPACESHIP);
	mPhysic->SetMask(ASTERO);
	mPhysic->SetMask(ALLY_ROCKET);
	mPhysic->SetMask(ENEMY_ROCKET);
	AddComponent<PhysicsComponent>(mPhysic);

	mTransform->SetScale(scale);
	XMFLOAT3 dirz = mTransform->GetDirectionZ();
	XMVECTOR velocity = XMLoadFloat3(&dirz) * mSpeed;
	XMStoreFloat3(&dirz, velocity);
	mPhysic->AddVelocity(dirz);
}

void Astero::OnUpdate(float deltaTime) { }

void Astero::OnDestroy() { }

void Astero::OnCollision(GameObject* go)
{
	if (!go->mId->IsBitMask(ASTERO)) {
		if (go->mId->IsBitMask(SPACESHIP)) 
			mToDestroy = true;
		
		else {
			LoseHp(1);
			if (go->mId->IsBitMask(ALLY_ROCKET) && mToDestroy) 
				GameObjectManager::GetInstance()->GetScore()->AddScore(mScoreValue);
		}
	}
}