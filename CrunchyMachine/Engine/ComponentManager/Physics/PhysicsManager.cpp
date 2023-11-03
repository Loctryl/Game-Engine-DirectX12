#include "PhysicsManager.h"
#include "EngineResources/PhysicsRessources.h"
#include "Engine/GameObject.h"
#include "Engine/Component/Transform.h"
#include "EngineResources/BitMask.h"

PhysicsManager::PhysicsManager()
{
	mComponentType = PHYSICS;
	mComponents = std::vector<PhysicsComponent*>();
	mCollisionGrid = std::vector<CollisionGrid*>();
}

PhysicsManager::~PhysicsManager()
{
	for (auto obj : mCollisionGrid)
		RELPTR(obj);

	mCollisionGrid.clear();
}

void PhysicsManager::CalculateNewPositions(float deltaTime)
{
	for (auto obj : mComponents) {
		if (obj) {
			obj->Move(deltaTime);
		}
	}
}

void PhysicsManager::ReCalculatePositions(PhysicsComponent* pc1, PhysicsComponent* pc2, float dist)
{
	Transform* transform1 = GetRootTransform(pc1);
	Transform* transform2 = GetRootTransform(pc2);

	XMFLOAT3 pos1 = transform1->GetPosition();
	XMFLOAT3 pos2 = transform2->GetPosition();

	//direction of pos1 to pos2
	XMFLOAT3 direction = { pos2.x - pos1.x, pos2.y - pos1.y, pos2.z - pos1.z };

	XMVECTOR vecDirection = XMLoadFloat3(&direction);
	vecDirection = XMVector4Normalize(vecDirection);

	XMStoreFloat3(&direction, vecDirection * dist / 2);

	pc1->AddVelocity(direction);
	pc2->AddVelocity(direction.x * -1, direction.y * -1, direction.z * -1);
	
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

			//Avoid collision check with parents
			if (iComponent->mGameObject->GetParent() == jComponent->mGameObject)
				continue;

			//Avoid collision check with children
			if (jComponent->mGameObject->GetParent() == iComponent->mGameObject)
				continue;

			//Test if the iComponent and the jComponent have a common collision mask, otherwise don't check collision
			if (iComponent->HasCommonMask(jComponent->GetBitMask()))
			{
				//Get grid position of each component.
				XMFLOAT3 iGridPos = iComponent->mGridPos;
				XMFLOAT3 jGridPos = jComponent->mGridPos;

				//Get the grid size of each component.
				int iGridSize = std::ceilf(iComponent->GetRadius() * 2 / GRID_SIZE);
				int jGridSize = std::ceilf(jComponent->GetRadius() * 2 / GRID_SIZE);

				//test distance to avoid useless collision test.
				if (std::abs(iGridPos.x - jGridPos.x) < iGridSize + jGridSize &&
					std::abs(iGridPos.y - jGridPos.y) < iGridSize + jGridSize &&
					std::abs(iGridPos.z - jGridPos.z) < iGridSize + jGridSize)
				{
					//cout << "test collision  {" << iGridPos.x << " ," << iGridPos.y << " ," << iGridPos.y << "} : {" << jGridPos.x << " ," << jGridPos.y << " ," << jGridPos.y << "}" << endl;

					//Test collision here
					float dist = iComponent->GetDistanceBetween(jComponent);
					if (dist < 0)
					{
						//Adapt position of the two game objects if they are both rigids
						if (iComponent->IsRigid() && jComponent->IsRigid())
							ReCalculatePositions(iComponent, jComponent, dist);

						iComponent->mGameObject->OnCollision(jComponent->mGameObject);
						jComponent->mGameObject->OnCollision(iComponent->mGameObject);
					}
				}
			}
		}
	}
}

void PhysicsManager::Update(float deltaTime)
{
	CalculateNewPositions(deltaTime);
	CheckCollision(deltaTime);
}

Transform* PhysicsManager::GetRootTransform(PhysicsComponent* physicsComponent)
{
	GameObject* go1 = physicsComponent->mGameObject;

	bool isRootFind = false;

	if (!go1->IsIndependant())
		while (!isRootFind) {
			GameObject* newGo = go1->GetParent();
			if (newGo) {
				if (newGo->IsIndependant())
					isRootFind = true;
				
				go1 = newGo;
			}
			else {
				isRootFind = true;
			}
		}

	return go1->mTransform;
}
