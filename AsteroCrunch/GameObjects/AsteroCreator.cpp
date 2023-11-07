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

	mSize = XMFLOAT2(480, 240);
}

void AsteroCreator::OnInit()
{
}

void AsteroCreator::OnUpdate(float deltaTime)
{
	XMFLOAT3 dirz = XMFLOAT3(0, 0, 1);
	XMVECTOR pos = XMLoadFloat3(&dirz);
	//pos *= (float)mCamera->GetFarZ() / 3;
	pos *= -30;
	mTransform->SetPosition(pos);


	if (rand() % 5 == 1) {

		XMFLOAT3 dirx = mTransform->GetDirectionX();
		XMFLOAT3 diry = mTransform->GetDirectionY();

		XMVECTOR xOffset = XMLoadFloat3(&dirx) * ((rand() % (int)mSize.x) - mSize.y);
		XMVECTOR yOffset = XMLoadFloat3(&diry) * ((rand() % (int)mSize.y) - mSize.y / 2);

		XMStoreFloat3(&dirx, xOffset);
		XMStoreFloat3(&diry, yOffset);

		Astero* asteroid = new Astero(this, 45, dirx, diry);
	}

}

void AsteroCreator::OnDestroy()
{
}

void AsteroCreator::OnCollision(GameObject* go)
{

}