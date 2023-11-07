#include "AsteroCreator.h"
#include "GameObjects/Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include <random>

AsteroCreator::AsteroCreator() : GameObject()
{
	mCamera = GameObjectManager::GetInstance()->GetCamera();


	//make it face the player 
	mTransform->SetRotation(mCamera->mTransform->GetRotation());
	mTransform->Rotate(XMFLOAT3(0, XM_PI, 0));
}

void AsteroCreator::OnInit()
{
}

void AsteroCreator::OnUpdate(float deltaTime)
{
	XMFLOAT3 dirz = XMFLOAT3(0,0,1);
	XMVECTOR pos = XMLoadFloat3(&dirz);
	pos *= mCamera->GetFarZ() / 3;
	mTransform->SetPosition(pos);

	if (rand() % 5 == 1) {
		XMFLOAT3 dirx = mTransform->GetDirectionX();
		XMFLOAT3 diry = mTransform->GetDirectionY();

		XMVECTOR xOffset = XMLoadFloat3(&dirx) * (rand() % 120 - 60);
		XMVECTOR yOffset = XMLoadFloat3(&diry) * (rand() % 60 - 30);

		XMStoreFloat3(&dirx, xOffset);
		XMStoreFloat3(&diry, yOffset);

		Astero* asteroid = new Astero(this, 1, dirx, diry);
	}
}

void AsteroCreator::OnDestroy()
{
}

void AsteroCreator::OnCollision(GameObject* go)
{

}