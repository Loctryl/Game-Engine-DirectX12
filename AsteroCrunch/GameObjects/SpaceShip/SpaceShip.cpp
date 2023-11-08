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
	mParts[3] = new SpaceShipPart();
	mParts[4] = new SpaceShipPart();
	mParts[5] = new SpaceShipPart();
	mParts[0]->AddParent(this);
	mParts[1]->AddParent(this);
	mParts[2]->AddParent(this);
	mParts[3]->AddParent(this);
	mParts[4]->AddParent(this);
	mParts[5]->AddParent(this);

	RenderComponent* cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[0]->AddComponent<RenderComponent>(cube);
	mParts[0]->mTransform->Roll(35);
	mParts[0]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	mParts[0]->mTransform->SetScale(1.8f, 0.1f, 0.2f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[1]->AddComponent<RenderComponent>(cube);
	mParts[1]->mTransform->Rotate(90, 0, -35);
	mParts[1]->mTransform->SetPosition(1.3f, -1.0f, 0.0f);
	mParts[1]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[2]->AddComponent<RenderComponent>(cube);
	mParts[2]->mTransform->Rotate(90, 0, 35);
	mParts[2]->mTransform->SetPosition(-1.3f, -1.0f, 0.0f);
	mParts[2]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	cube = new RenderComponent(CUBE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[3]->AddComponent<RenderComponent>(cube);
	mParts[3]->mTransform->Roll(-35);
	mParts[3]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	mParts[3]->mTransform->SetScale(1.8f, 0.1f, 0.2f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[4]->AddComponent<RenderComponent>(cube);
	mParts[4]->mTransform->Rotate(90, 0, 35);
	mParts[4]->mTransform->SetPosition(1.3f, 1.0f, 0.0f);
	mParts[4]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[5]->AddComponent<RenderComponent>(cube);
	mParts[5]->mTransform->Rotate(90, 0, -35);
	mParts[5]->mTransform->SetPosition(-1.3f, 1.0f, 0.0f);
	mParts[5]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	mId->SetMask(0);
}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	AddComponent<RenderComponent>(comp);
	physic = new PhysicsComponent(mTransform, true, 3);
	physic->SetMask(1);
	AddComponent<PhysicsComponent>(physic);
	mTransform->SetPosition(0.0f, 0.0f, 0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	XMFLOAT3 pos = mTransform->GetWorldPosition();
	//Rotate the cam in function of the mouse pos and the screen center
	XMFLOAT2 inputMouse = mInput->GetMouseDelta();

	physic->AddRotationVelocity(inputMouse.y * 45.0f * MOUSE_SENSIBILITY * deltaTime, 0, 0);
	physic->AddRotationVelocity(0, inputMouse.x * 45.0f * MOUSE_SENSIBILITY * deltaTime, 0);

	HandleInput(deltaTime);
}

void SpaceShip::OnDestroy() { }

void SpaceShip::OnCollision(GameObject* gt)
{

}

void SpaceShip::HandleInput(float deltaTime)
{
	//get the inputs to move the cam
	switch (mInput->GetInputStates()[0]) {
	case Input::KEYHOLD:
		XMFLOAT3 movement = mTransform->GetDirectionZ();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[1]) {
	case Input::KEYHOLD:
		XMFLOAT3 movement = mTransform->GetDirectionX();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[2]) {
	case Input::KEYHOLD:
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
	case Input::KEYHOLD:
		XMFLOAT3 movement = mTransform->GetDirectionX();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[8]) {
	case Input::KEYHOLD:

		physic->AddRotationVelocity(0,0,mCurrentRotationSpeed * deltaTime);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[9]) {
	case Input::KEYHOLD:

		physic->AddRotationVelocity(0, 0, -mCurrentRotationSpeed * deltaTime);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[10]) {
	case Input::KEYHOLD:
		XMFLOAT3 movement = mTransform->GetDirectionY();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * -mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[11]) {
	case Input::KEYHOLD:
		XMFLOAT3 movement = mTransform->GetDirectionY();
		XMVECTOR vect = XMLoadFloat3(&movement);
		XMVector3Normalize(vect);
		XMStoreFloat3(&movement, vect * mCurrentAcceleration * deltaTime);

		physic->AddVelocity(movement);
		break;
	default:
		break;
	}

	switch (mInput->GetInputStates()[5]) {
	case Input::KEYDOWN:
		Rocket * rocket = new Rocket(this);
		break;
	}
}


void SpaceShip::SetCam(Camera* cam) {
	mCam = cam;
	//mCam->mTransform->Translate(0, 0, -5.0f);
	cam->AddParent(this);
}