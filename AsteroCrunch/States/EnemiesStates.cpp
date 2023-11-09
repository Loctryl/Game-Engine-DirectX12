#include "EnemiesStates.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"
#include "Entity.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "GameObjects/Rocket.h"
#include "Resources/framework.h"

#pragma region Fighting

Fighting::Fighting(float fireRate, float speed) : BaseState()
{
	mPlayer = GameObjectManager::GetInstance()->GetCamera()->GetParent();
	mSpeed = speed;
	mFireRate = fireRate;
}

Fighting::~Fighting()
{
}

void Fighting::OnStart()
{
}

void Fighting::OnUpdate(float deltatime)
{
	mFireCooldown += deltatime;

	XMFLOAT3 pos = mGameObject->mTransform->GetWorldPosition();
	XMFLOAT3 playerPosition = mPlayer->mTransform->GetWorldPosition();

	XMFLOAT3 direction = { playerPosition.x - pos.x, playerPosition.y - pos.y, playerPosition.z - pos.z };

	XMVECTOR vecDirection = XMLoadFloat3(&direction);
	vecDirection = XMVector4Normalize(vecDirection);

	XMStoreFloat3(&direction, vecDirection);

	XMFLOAT3 dirZ = mGameObject->mTransform->GetDirectionZ();

	vecDirection = XMVector3AngleBetweenVectors(XMLoadFloat3(&direction), XMLoadFloat3(&dirZ));

	XMFLOAT3 angleBetween;
	XMStoreFloat3(&angleBetween, vecDirection);

	mGameObject->mTransform->Pitch(180 - XMConvertToDegrees(angleBetween.x));
	mGameObject->mTransform->Yaw(180 - XMConvertToDegrees(angleBetween.y));

	if (std::abs(pos.x - playerPosition.x) < ATTACK_RANGE &&
		std::abs(pos.y - playerPosition.y) < ATTACK_RANGE &&
		std::abs(pos.z - playerPosition.z) < ATTACK_RANGE
		)
	{
		if (mFireCooldown > 1 / mFireRate) {
			Rocket* rocket = new Rocket(400);
			rocket->mTransform->SetPosition(mGameObject->mTransform->GetWorldPosition());
			rocket->mTransform->SetRotation(mGameObject->mTransform->GetRotation());
			rocket->mId->SetMask(ENEMY_ROCKET);

			mFireCooldown = 0;
		}
	}
	else
	{
		PhysicsComponent* physic = mGameObject->GetComponent<PhysicsComponent>(PHYSICS);
		physic->SetVelocity(direction.x * mSpeed, direction.y * mSpeed, direction.z * mSpeed);
	}
}

void Fighting::OnEnd()
{
}

#pragma endregion

#pragma region Flee


Flee::Flee(float speed)
{
	mPlayer = GameObjectManager::GetInstance()->GetCamera()->GetParent();
	mSpeed = speed;
}

Flee::~Flee()
{
}

void Flee::OnStart()
{
	XMFLOAT3 pos = mGameObject->mTransform->GetWorldPosition();
	XMFLOAT3 playerPosition = mPlayer->mTransform->GetWorldPosition();

	XMFLOAT3 direction = { playerPosition.x - pos.x, playerPosition.y - pos.y, playerPosition.z - pos.z };

	XMVECTOR vecDirection = XMLoadFloat3(&direction);
	vecDirection = XMVector4Normalize(vecDirection);

	XMStoreFloat3(&direction, vecDirection);

	XMFLOAT3 dirZ = mGameObject->mTransform->GetDirectionZ();

	vecDirection = XMVector3AngleBetweenVectors(XMLoadFloat3(&dirZ), XMLoadFloat3(&direction));

	XMFLOAT3 angleBetween;
	XMStoreFloat3(&angleBetween, vecDirection);

	mGameObject->mTransform->Pitch(180 - XMConvertToDegrees(angleBetween.x));
	mGameObject->mTransform->Yaw(180 - XMConvertToDegrees(angleBetween.y));

	PhysicsComponent* physic = mGameObject->GetComponent<PhysicsComponent>(PHYSICS);
	physic->SetVelocity(direction.x * -mSpeed, direction.y * -mSpeed, direction.z * -mSpeed);
}

void Flee::OnUpdate(float deltatime)
{
}

void Flee::OnEnd()
{
}

#pragma endregion