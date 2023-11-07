#include "Rocket.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Input.h"
#include "EngineResources/Color.h"


Rocket::Rocket() : GameObject()
{
	

}

void Rocket::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE);
	comp->SetColor(Color::red());
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* phy = new PhysicsComponent(mTransform, false, 1);
	phy->SetMask(1);
	AddComponent<PhysicsComponent>(phy);

	mTransform->SetPosition(mParent->mTransform->GetPosition());
	mTransform->SetRotation(mParent->mTransform->GetRotation());
}

void Rocket::OnUpdate(float deltaTime)
{
	XMFLOAT3 something = mTransform->GetDirz();
	XMVECTOR tempTranslate = XMLoadFloat3(&something) * 0.5f;
	XMFLOAT3 translate;
	XMStoreFloat3(&translate, tempTranslate);


	mTransform->Translate(translate);

}

void Rocket::OnDestroy()
{
}

void Rocket::OnCollision(GameObject* gt)
{

}