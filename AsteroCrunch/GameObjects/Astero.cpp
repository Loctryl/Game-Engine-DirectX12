#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "States/DefaultState.h"
#include "EngineResources/Color.h"
#include <random>


Astero::Astero(GameObject* parent , float speed, XMFLOAT3 xOffset, XMFLOAT3 yOffset) : GameObject()
{
	mParent = parent;
	mTransform->SetRotation(mParent->mTransform->GetRotation());
	mTransform->SetPosition(mParent->mTransform->GetPosition());
	mTransform->Translate(xOffset);
	mTransform->Translate(yOffset);
	mSpeed = speed;
}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(SPHERE));
	GetComponent<RenderComponent>(RENDER)->SetColor(Color::cyan());
	physics = new PhysicsComponent(mTransform, true, 1);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	XMFLOAT3 dirz = mTransform->GetDirz();
	XMVECTOR velocity = XMLoadFloat3(&dirz) * mSpeed;
	XMStoreFloat3(&dirz, velocity);
	physics->AddVelocity(dirz);
}

void Astero::OnUpdate(float deltaTime)
{
	
}

void Astero::OnDestroy()
{
}

void Astero::OnCollision(GameObject* go)
{

}
