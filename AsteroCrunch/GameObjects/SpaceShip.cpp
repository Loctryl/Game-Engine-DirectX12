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

SpaceShip::SpaceShip() : GameObject()
{
	mInput = Input::GetInstance();
}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* phy = new PhysicsComponent(mTransform, true, 1);
	AddComponent<PhysicsComponent>(phy);
	mTransform->SetPosition(1.0f, 0.0f, 0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{

	//Rotate the cam in function of the mouse pos and the screen center
	XMFLOAT2 inputMouse = mInput->GetMousePosition(Window::GetHWND());
	XMVECTOR mousePos = XMLoadFloat2(&inputMouse);
	XMFLOAT2 floatScreenSize = D3DApp::GetInstance()->GetWindowSize();
	XMVECTOR screenSize = XMLoadFloat2(&floatScreenSize);
	XMFLOAT2 tempMousePos;
	XMStoreFloat2(&tempMousePos, mousePos - (screenSize / 2));

	XMFLOAT3 centeredMousPos = XMFLOAT3(tempMousePos.x, tempMousePos.y, 0);
	XMFLOAT3 camDirz = mCam->mTransform->GetDirz();
	XMVECTOR tempDir = XMLoadFloat3(&camDirz);
	tempDir += XMLoadFloat3(&centeredMousPos);
	XMVector3Normalize(tempDir);
	tempDir /= 5000;

	XMFLOAT3 almostFinalDir;
	XMStoreFloat3(&almostFinalDir, tempDir);
	XMFLOAT3 finalDir = XMFLOAT3(almostFinalDir.y, almostFinalDir.x, almostFinalDir.z);
	mCam->mTransform->Rotate(finalDir);

	//recenter Cursor
	RECT r;
	GetWindowRect(Window::GetHWND(), &r);
	SetCursorPos((D3DApp::GetInstance()->GetWindowSize().x / 2) + r.left + 8, (D3DApp::GetInstance()->GetWindowSize().y / 2) + r.top + 31);

	//get the inputs to move the cam
	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mCam->mTransform->Translate(0, 0, 9 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mCam->mTransform->Translate(-9 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mCam->mTransform->Translate(0, 0, -9 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mCam->mTransform->Translate(9 * deltaTime, 0, 0);
		break;
	default:
		break;
	}

	//Calculate the new focus of the camera in function of it's direction
	XMFLOAT3 tempdirz = mCam->mTransform->GetDirz();
	XMVECTOR dirz = XMLoadFloat3(&tempdirz);
	XMFLOAT4 camRot = mCam->mTransform->GetRotation();
	XMVECTOR rotation = XMLoadFloat4(&camRot);
	XMVECTOR preTranslateDir = XMVector3Rotate(dirz, rotation);
	XMFLOAT3 camPos = mCam->mTransform->GetPosition();
	XMVECTOR dir = preTranslateDir + XMLoadFloat3(&camPos);
	XMFLOAT3 camTarget = mCam->GetTarget();
	XMStoreFloat3(&camTarget, dir);
	mCam->SetTarget(camTarget);


	//Set pos and rot equal to camera's
	mTransform->SetPosition(mCam->mTransform->GetPosition());
	mTransform->SetRotation(mCam->mTransform->GetRotation());

	switch (static_cast<int>(mInput->GetInputStates()[5])) {
	case 1:
		Rocket* rocket = new Rocket();
		GameObjectManager::GetInstance()->AddGameObject(rocket);
		rocket->AddParent(this);
		break;
	}
}

void SpaceShip::OnDestroy() { }

void SpaceShip::OnCollision(GameObject* gt)
{

}

void SpaceShip::SetCam(Camera* cam) {
	mCam = cam;
}