#include "AsteroCreator.h"
#include "GameObjects/Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Resources/framework.h"
#include <random>

AsteroCreator::AsteroCreator() : GameObject()
{
	mCamera = GameObjectManager::GetInstance()->GetCamera();

	//make it face the player 
	mTransform->SetRotation(mCamera->mTransform->GetRotation());
	mTransform->Rotate(XMFLOAT3(0, XM_PI, 0));

	mSize = XMFLOAT2(BORDER_SIZE*2, BORDER_SIZE*2);
}

void AsteroCreator::OnInit()
{
}

void AsteroCreator::OnUpdate(float deltaTime)
{
	XMFLOAT3 dirz = XMFLOAT3(0, 0, 1);
	XMVECTOR pos = XMLoadFloat3(&dirz);
	pos *= (float)mCamera->GetFarZ() + mCamera->mTransform->GetWorldPosition().z;
	
	mTransform->SetPosition(pos);


	if (rand() % 20 == 1) {

		XMFLOAT3 dirx = mTransform->GetDirectionX();
		XMFLOAT3 diry = mTransform->GetDirectionY();


		XMVECTOR xOffset = XMLoadFloat3(&dirx) * ((rand() % (int)mSize.x) - mSize.x / 2);
		XMVECTOR yOffset = XMLoadFloat3(&diry) * ((rand() % (int)mSize.y) - mSize.y / 2);
		XMFLOAT3 creatorPos = mTransform->GetPosition();
		XMVECTOR basePos = XMLoadFloat3(&creatorPos);
	
		XMFLOAT3 finalPos;
		XMStoreFloat3(&finalPos, xOffset + yOffset + basePos);

		Astero* asteroid = new Astero(finalPos, mTransform->GetRotation(), 45);
	}

}

void AsteroCreator::OnDestroy()
{
}

void AsteroCreator::OnCollision(GameObject* go)
{

}