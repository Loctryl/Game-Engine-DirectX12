#pragma once
#include "Engine/GameObject.h"

// Base class for all entities in the game, providing HP management
class Entity : public GameObject
{
	virtual void OnInit() override = 0;
	virtual void OnUpdate(float deltaTime) override = 0;
	virtual void OnDestroy() override = 0;
	virtual void OnCollision(GameObject* go) override = 0;

	int mCurrentHp = 0;
	int mMaxHp = 0;
	
public: 
	void InitMaxHp(int maxHp);
	void LoseHp(int qty);
	void GainHp(int qty);
	inline int GetCurrHp() const { return mCurrentHp; }
	inline int GetMaxHp() const { return mMaxHp; }

	inline void SetCurrHp(int amount) { mCurrentHp = amount; }
	
	int mScoreValue;
};