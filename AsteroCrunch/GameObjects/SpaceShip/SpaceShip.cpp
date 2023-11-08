#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Input.h"
#include "GameObjects/Rocket.h"
#include "Engine/GameObjectManager.h"
#include "DirectX12/D3DApp.h"
#include "Window/Window.h"	
#include "Engine/Component/Camera.h"
#include "SpaceShipPart.h"
#include "Resources/framework.h"

SpaceShip::SpaceShip() : GameObject()
{
	mInput = Input::GetInstance();
	mParts[0] = new SpaceShipPart();
	mParts[1] = new SpaceShipPart();
	mParts[2] = new SpaceShipPart();
	mParts[0]->AddParent(this);
	mParts[1]->AddParent(this);
	mParts[2]->AddParent(this);

	mParts[0]->AddComponent<RenderComponent>(new RenderComponent(CUBE, LITCOLOR));
	mParts[0]->mTransform->SetScale(1.5f, 0.2f, 0.2f);

	mParts[1]->AddComponent<RenderComponent>(new RenderComponent(LOSANGE, LITCOLOR));
	mParts[1]->mTransform->Rotate(0, 90, 0);
	mParts[1]->mTransform->SetPosition(1.5f, 0.0f, 0.0f);
	mParts[1]->mTransform->SetScale(0.1f, 1.0f, 1.0f);

	mParts[2]->AddComponent<RenderComponent>(new RenderComponent(LOSANGE, LITCOLOR));
	mParts[2]->mTransform->Rotate(0, 90, 0);
	mParts[2]->mTransform->SetPosition(-1.5f, 0.0f, 0.0f);
	mParts[2]->mTransform->SetScale(0.1f, 1.0f, 1.0f);
}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	AddComponent<RenderComponent>(comp);
	physic = new PhysicsComponent(mTransform, true, 1);
	AddComponent<PhysicsComponent>(physic);
	mTransform->SetPosition(0.0f, 0.0f, 0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{

	//Rotate the cam in function of the mouse pos and the screen center
	XMFLOAT2 inputMouse = mInput->GetMouseDelta();
	
	XMFLOAT3 finalDir = XMFLOAT3(inputMouse.y * 45.0f * MOUSE_SENSIBILITY * deltaTime, inputMouse.x * 45.0f * MOUSE_SENSIBILITY * deltaTime, 0);
	mTransform->Rotate(finalDir);

	HandleInput(deltaTime);
}

void SpaceShip::OnDestroy() { }

void SpaceShip::OnCollision(GameObject* gt)
{

}

void SpaceShip::HandleInput(float deltaTime)
{
	//get the inputs to move the cam
	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionZ();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionX();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionZ();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionX();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[8])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionZ();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentRotationSpeed * deltaTime);

		mTransform->Rotate(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[9])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionZ();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentRotationSpeed * deltaTime);

		mTransform->Rotate(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[10])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionY();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[11])) {
	case 3:
		XMFLOAT3 movement = mTransform->GetDirectionY();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (static_cast<int>(mInput->GetInputStates()[5])) {
	case 1:
		Rocket * rocket = new Rocket(this);
		break;
	}
}


void SpaceShip::SetCam(Camera* cam) {
	mCam = cam;
	//mCam->mTransform->Translate(0, 0, -5.0f);
	cam->AddParent(this);
}