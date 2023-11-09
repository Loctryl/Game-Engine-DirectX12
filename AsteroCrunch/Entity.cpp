#include "Entity.h"
#include "Resources/framework.h"
#include "DirectX12/ParticleEmitter.h"
#include "EngineResources/Color.h"
#include "Engine/Component/Transform.h"

void Entity::OnInit()
{
}

void Entity::OnUpdate(float deltaTime)
{
}

void Entity::OnDestroy()
{
}

void Entity::OnCollision(GameObject* gt)
{
}

void Entity::InitMaxHp(int maxHp)
{
	mMaxHp = maxHp;
	mCurrentHp = mMaxHp;
}

void Entity::LoseHp(int qty)
{
	mCurrentHp -= qty;
	if (!mCurrentHp) {
		ToDestroy = true;
		if (this->mId->IsBitMask(ASTERO)) 
		{
			ParticleEmitter* part = new ParticleEmitter(RADIAL, 20, XMFLOAT3(1, 1, 1), 2, Color::darkgrey(), 360, this->mTransform->GetScale().y / 10, this->mTransform->GetPosition());
		}
		else if (this->mId->IsBitMask(ENEMY))
		{
			ParticleEmitter* part = new ParticleEmitter(RADIAL, 12, XMFLOAT3(0.6, 0.6, 0.6), 2, Color::grey(), 360, this->mTransform->GetScale().y / 5, this->mTransform->GetPosition());
		}
	}
}

void Entity::GainHp(int qty)
{
	mCurrentHp += qty;
	if (mCurrentHp > mMaxHp) mCurrentHp = mMaxHp;
}

void Entity::SetCurrHp(int amount)
{
	mCurrentHp = amount;
}
