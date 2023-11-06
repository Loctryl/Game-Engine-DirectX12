#include "AsteroCreator.h"
#include "GameObjects/Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"

AsteroCreator::AsteroCreator() : GameObject()
{
}

void AsteroCreator::OnInit()
{
}

void AsteroCreator::OnUpdate(float deltaTime)
{
	XMFLOAT3 dirz = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetDirz();
	XMVECTOR pos = XMLoadFloat3(&dirz);
	//pos *= GameObjectManager::GetInstance()->GetCamera()->GetFarZ();
	pos *= 30;
	mTransform->SetPosition(pos);

	Astero* asteroid = new Astero(this, 1);
	GameObjectManager::GetInstance()->AddGameObject(asteroid);
}

void AsteroCreator::OnDestroy()
{
}

void AsteroCreator::OnCollision(GameObject* go)
{

}