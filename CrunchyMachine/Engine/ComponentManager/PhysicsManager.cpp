#include "PhysicsManager.h"
#include "Resources/PhysicsRessources.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"

PhysicsManager::PhysicsManager()
{
	mComponentType = PHYSICS;
	mComponents = std::vector<PhysicsComponent*>();
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::CalculateNewPositions(float deltaTime)
{
	for (auto obj : mComponents) {
		obj->Move(deltaTime);
	}
}

void PhysicsManager::CheckCollision(float deltaTime)
{
	for (int i = 0; i < mComponents.size(); i++) {
		for (int j = i + 1; j < mComponents.size(); j++) {
			if (mComponents[i]->IsColliding(mComponents[j]))
			{
				mComponents[i]->mGameObject->OnCollision(mComponents[j]->mGameObject);
				mComponents[j]->mGameObject->OnCollision(mComponents[i]->mGameObject);
			}
		}
	}
}

void PhysicsManager::Update(float deltaTime)
{
	CalculateNewPositions(deltaTime);
	CheckCollision(deltaTime);
}
