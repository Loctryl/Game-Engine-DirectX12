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
#include "UI/Life.h"
#include "GameObjects/Border.h"

SpaceShip::SpaceShip() : Entity()
{
	mInput = Input::GetInstance();
	InitMaxHp(3);
	InitSpaceShipParts();
	InitBorders();
}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	AddComponent<RenderComponent>(comp);
	physic = new PhysicsComponent(mTransform, true, 3);
	physic->SetMask(1);
	physic->SetMask(5);
	AddComponent<PhysicsComponent>(physic);
	mTransform->SetPosition(0.0f, 0.0f, 0.0f);

	//init Id
	mId->SetMask(0);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	XMFLOAT3 pos = mTransform->GetWorldPosition();
	//Rotate the cam in function of the mouse pos and the screen center
	XMFLOAT2 inputMouse = mInput->GetMouseDelta();

	physic->AddRotationVelocity(inputMouse.y * 45.0f * MOUSE_SENSIBILITY * deltaTime, 0, 0);
	physic->AddRotationVelocity(0, inputMouse.x * 45.0f * MOUSE_SENSIBILITY * deltaTime, 0);

	HandleInput(deltaTime);

	XMFLOAT3 velocity = physic->GetRotationVelocity();

	physic->ClampVelocity(-mMaxSpeed, mMaxSpeed);
	physic->ClampRotationVelocity(-mMaxRotationSpeed, mMaxRotationSpeed);
	UpdateBorders();
}

void SpaceShip::OnDestroy()
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

		mFOValteration += FOV_MOUVEMENT_SCALING * deltaTime;
		if (mFOValteration > mMaxFOValteration) mFOValteration = mMaxFOValteration;
		if (mFOValteration > 0)
			mCam->SetFOV(DEFAULT_FOV + mFOValteration);
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

		mFOValteration -= FOV_MOUVEMENT_SCALING * deltaTime;
		if (mFOValteration < -mMaxFOValteration) mFOValteration = -mMaxFOValteration;
		if (mFOValteration > 0)
			mCam->SetFOV(DEFAULT_FOV + mFOValteration);
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

		physic->AddRotationVelocity(0, 0, mCurrentRotationSpeed * deltaTime);
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
		Rocket* rocket = new Rocket(this);
		rocket->mTransform->SetPosition(mTransform->GetWorldPosition());
		rocket->mTransform->SetRotation(mTransform->GetRotation());
		break;
	}
}

void SpaceShip::SetCam(Camera* cam) {
	mCam = cam;
	//mCam->mTransform->Translate(0, 0, -5.0f);
	cam->AddParent(this);
}

void SpaceShip::OnCollision(GameObject* go)
{
	if (go->mId->IsBitMask(2)) {
		cout << "ouch" << endl;
		SetCurrHp(GetCurrHp() - 1);
		mLife->LooseLifeOnUI(GetCurrHp());
		if (GetCurrHp() == 0) {
			GameObjectManager::GetInstance()->EndGame();
		}
	}
}

void SpaceShip::InitSpaceShipParts()
{
	mParts[0] = new SpaceShipPart();
	mParts[1] = new SpaceShipPart();
	mParts[2] = new SpaceShipPart();
	mParts[3] = new SpaceShipPart();
	mParts[0]->AddParent(this);
	mParts[1]->AddParent(this);
	mParts[2]->AddParent(this);
	mParts[3]->AddParent(this);

	//cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	//mParts[0]->AddComponent<RenderComponent>(cube);
	//mParts[0]->mTransform->Roll(35);
	//mParts[0]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	//mParts[0]->mTransform->SetScale(1.8f, 0.1f, 0.2f);

	RenderComponent* cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[0]->AddComponent<RenderComponent>(cube);
	mParts[0]->mDigit = 0;
	mParts[0]->mTransform->Rotate(90, 0, -35);
	mParts[0]->mTransform->SetPosition(1.3f, -1.0f, 0.0f);
	mParts[0]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[1]->AddComponent<RenderComponent>(cube);
	mParts[1]->mDigit = 0;
	mParts[1]->mTransform->Rotate(90, 0, 35);
	mParts[1]->mTransform->SetPosition(-1.3f, -1.0f, 0.0f);
	mParts[1]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	//cube = new RenderComponent(CUBE, LITCOLOR);
	//cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	//mParts[3]->AddComponent<RenderComponent>(cube);
	//mParts[3]->mTransform->Roll(-35);
	//mParts[3]->mTransform->SetPosition(0.0f, 0.0f, 0.0f);
	//mParts[3]->mTransform->SetScale(1.8f, 0.1f, 0.2f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[2]->AddComponent<RenderComponent>(cube);
	mParts[2]->mDigit = 0;
	mParts[2]->mTransform->Rotate(90, 0, 35);
	mParts[2]->mTransform->SetPosition(1.3f, 1.0f, 0.0f);
	mParts[2]->mTransform->SetScale(0.2f, 0.5f, 0.7f);

	cube = new RenderComponent(LOSANGE, LITCOLOR);
	cube->SetColor(XMFLOAT4(0.5f, 0.5f, 0.5f, 1.f));
	mParts[3]->AddComponent<RenderComponent>(cube);
	mParts[3]->mDigit = 0;
	mParts[3]->mTransform->Rotate(90, 0, -35);
	mParts[3]->mTransform->SetPosition(-1.3f, 1.0f, 0.0f);
	mParts[3]->mTransform->SetScale(0.2f, 0.5f, 0.7f);
}

void SpaceShip::InitBorders()
{
	mBorders[0] = new Border();
	mBorders[1] = new Border();
	mBorders[2] = new Border();
	mBorders[3] = new Border();
	XMFLOAT3 pos = mTransform->GetPosition();
	mBorders[0]->mTransform->SetPosition(BORDER_SIZE, pos.y, pos.z);
	mBorders[1]->mTransform->SetPosition(-BORDER_SIZE, pos.y, pos.z);
	mBorders[2]->mTransform->SetPosition(pos.x, BORDER_SIZE, pos.z);
	mBorders[3]->mTransform->SetPosition(pos.x, -BORDER_SIZE, pos.z);

}

void SpaceShip::UpdateBorders()
{
	XMFLOAT3 pos = mTransform->GetPosition();
	mBorders[0]->mTransform->SetPosition(BORDER_SIZE, pos.y, pos.z);
	mBorders[1]->mTransform->SetPosition(-BORDER_SIZE, pos.y, pos.z);
	mBorders[2]->mTransform->SetPosition(pos.x, BORDER_SIZE, pos.z);
	mBorders[3]->mTransform->SetPosition(pos.x, -BORDER_SIZE, pos.z);
}
