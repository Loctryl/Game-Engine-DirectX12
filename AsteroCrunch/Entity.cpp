#include "Entity.h"

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
	}
}

void Entity::GainHp(int qty)
{
	mCurrentHp += qty;
	if (mCurrentHp > mMaxHp) mCurrentHp = mMaxHp;
}
