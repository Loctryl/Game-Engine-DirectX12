#include "Enemy.h"
#include "GameObjects/Player/SpaceShipPart.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "States/EnemiesStates.h"
#include "Engine/GameObjectManager.h"
#include "UI/Score.h"
#include "Resources/framework.h"
#include <vector>

Enemy::Enemy()
{
	InitSpaceShipParts();
}

Enemy::~Enemy()
{
	mPhysic = nullptr;
	mStateMachine = nullptr;
	for(int i = 0; i < 5 ; i++)
	{
		mParts[i]->mToDestroy = true;
		mParts[i] = nullptr;
	}
}


void Enemy::OnInit()
{
	RenderComponent* render = new RenderComponent(SPHERE, LIT_COLOR);
	render->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	AddComponent<RenderComponent>(render);

	mPhysic = new PhysicsComponent(mTransform, true, 3.0f);
	mPhysic->SetMask(ALLY_ROCKET);
	mPhysic->SetMask(ASTERO);
	mPhysic->SetMask(SPACESHIP);
	mPhysic->SetMask(ENEMY);

	AddComponent<PhysicsComponent>(mPhysic);

	mStateMachine = new StateMachineComponent(new Fighting(mFireRate, mCurrentAcceleration));
	AddComponent<StateMachineComponent>(mStateMachine);

	mTransform->SetScale(2.5f);

	mId->SetMask(ENEMY);
	SetCurrHp(5);
	mScoreValue = 4000;

}

void Enemy::OnUpdate(float deltaTime)
{
	if (GetCurrHp() <= 2 && !mIsFleeing) {
		mStateMachine->SwitchState(new Flee(mCurrentAcceleration));
		mIsFleeing = true;
	}
}

void Enemy::OnDestroy() { }

void Enemy::OnCollision(GameObject* go)
{
	if (go->mId->IsBitMask(ALLY_ROCKET) || go->mId->IsBitMask(ASTERO) || go->mId->IsBitMask(SPACESHIP)) {
		LoseHp(1);
		if (go->mId->IsBitMask(ALLY_ROCKET)) GameObjectManager::GetInstance()->GetScore()->AddScore(mScoreValue);
	}
}

void Enemy::InitSpaceShipParts()
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

	RenderComponent* cube = new RenderComponent(CUBE, LIT_COLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[0]->AddComponent<RenderComponent>(cube);
	mParts[0]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	mParts[0]->mTransform->SetScale(1.2f, 0.1f, 0.2f);
	mParts[0]->mDigit = 0;

	cube = new RenderComponent(CUBE, LIT_COLOR);
	cube->SetColor(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.f));
	mParts[1]->AddComponent<RenderComponent>(cube);
	mParts[1]->mTransform->SetPosition(1.2f, 0.0f, 0.0f);
	mParts[1]->mTransform->SetScale(0.05f, 1.0f, 1.2f);
	mParts[1]->mDigit = 0;

	cube = new RenderComponent(CUBE, LIT_COLOR);
	cube->SetColor(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.f));
	mParts[2]->AddComponent<RenderComponent>(cube);
	mParts[2]->mTransform->SetPosition(-1.2f, 0.0f, 0.0f);
	mParts[2]->mTransform->SetScale(0.05f, 1.4f, 1.0f);
	mParts[2]->mDigit = 0;

	cube = new RenderComponent(CUBE, LIT_COLOR);
	cube->SetColor(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.f));
	mParts[3]->AddComponent<RenderComponent>(cube);
	mParts[3]->mTransform->SetPosition(1.2f, 0.0f, 0.0f);
	mParts[3]->mTransform->SetScale(0.05f, 1.4f, 1.0f);
	mParts[3]->mDigit = 0;

	cube = new RenderComponent(CUBE, LIT_COLOR);
	cube->SetColor(XMFLOAT4(0.1f, 0.1f, 0.1f, 1.f));
	mParts[4]->AddComponent<RenderComponent>(cube);
	mParts[4]->mTransform->SetPosition(-1.2f, 0.0f, 0.0f);
	mParts[4]->mTransform->SetScale(0.05f, 1.0f, 1.2f);
	mParts[4]->mDigit = 0;
}