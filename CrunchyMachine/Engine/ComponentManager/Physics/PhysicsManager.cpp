#include "PhysicsManager.h"
#include "Resources/PhysicsRessources.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"
#include "Resources/BitMask.h"
#include "Engine/ComponentManager/Physics/CollisionGrid.h"

PhysicsManager::PhysicsManager()
{
	mComponentType = PHYSICS;
	mComponents = std::vector<PhysicsComponent*>();
	mCollisionGrid = std::vector<CollisionGrid*>();
}

PhysicsManager::~PhysicsManager()
{
	for (auto obj : mCollisionGrid)
		delete obj;

	mCollisionGrid.clear();
}

void PhysicsManager::CalculateNewPositions(float deltaTime)
{
	for (auto obj : mComponents) {
		obj->Move(deltaTime);
	}
}

void PhysicsManager::ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2)
{
}

void PhysicsManager::CheckCollision(float deltaTime)
{
	for (int i = 0; i < mComponents.size(); i++) {
		PhysicsComponent* iComponent = mComponents[i];

		//If the component need to be destroy don't check collsion
		if (iComponent->mGameObject->ToDestroy)
			continue;

		for (int j = i + 1; j < mComponents.size(); j++) {
			PhysicsComponent* jComponent = mComponents[j];

			//If the component need to be destroy don't check collsion
			if (jComponent->mGameObject->ToDestroy)
				continue;

			//Test if the iComponent and the jComponent have a common collision mask, otherwise don't check collision
			if(iComponent->HasCommonMask(jComponent->GetBitMask()))

				//Test collision here
				if (iComponent->IsColliding(jComponent))
				{
					//Adapt position of the two game objects if they are both rigids
					if(iComponent->IsRigid() && jComponent->IsRigid())
						ReCalculatePositions(iComponent, jComponent);

					iComponent->mGameObject->OnCollision(jComponent->mGameObject);
					jComponent->mGameObject->OnCollision(iComponent->mGameObject);
				}
		}
	}
}

void PhysicsManager::Update(float deltaTime)
{
	CalculateNewPositions(deltaTime);
	CheckCollision(deltaTime);
}
