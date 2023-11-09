#include "EnemiesCreator.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/Transform.h"
#include "Engine/GameObjectManager.h"
#include "Resources/framework.h"
#include "Enemy.h"

void EnemiesCreator::OnInit()
{

}

void EnemiesCreator::OnUpdate(float deltaTime)
{
	mTransform->SetPosition(mCamera->mTransform->GetWorldPosition());

	mSpawnCooldown += deltaTime;

	if (mSpawnCooldown > mSpawnDelay) {
		int xOffset = (rand() % (int)mSize) + mSize/2;
		int yOffset = (rand() % (int)mSize) + mSize/2;
		int zOffset = (rand() % (int)mSize) + mSize/2;

		if (xOffset % 2 == 1) xOffset = -xOffset;
		if (yOffset % 2 == 1) yOffset = -yOffset;
		if (zOffset % 2 == 1) zOffset = -zOffset;

		XMFLOAT3 creatorPos = mTransform->GetPosition();	

		Enemy* enemy = new Enemy();
		enemy->mTransform->SetPosition(creatorPos.x + xOffset, creatorPos.y + yOffset, creatorPos.z + zOffset);

		mSpawnCooldown = 0;
	}
}

void EnemiesCreator::OnDestroy()
{
}

void EnemiesCreator::OnCollision(GameObject* gt)
{
}

EnemiesCreator::EnemiesCreator() : GameObject()
{
	mCamera = GameObjectManager::GetInstance()->GetCamera();
	mTransform->SetPosition(mCamera->mTransform->GetWorldPosition());
	mSize = BORDER_SIZE * 3;
}

EnemiesCreator::~EnemiesCreator()
{
}
