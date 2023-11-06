#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Input.h"
#include "GameObjects/Rocket.h"
#include "Engine/GameObjectManager.h"

SpaceShip::SpaceShip() : GameObject()
{
	mInput = Input::GetInstance();
}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE, 0);
	AddComponent<RenderComponent>(comp);
	PhysicsComponent* phy = new PhysicsComponent(mTransform, true, 1);
	AddComponent<PhysicsComponent>(phy);

	mTransform->SetPosition(1.0f, 0.0f, 0.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	mTransform->SetPosition(mParent->mTransform->GetPosition());
	mTransform->SetRotation(mParent->mTransform->GetRotation());

	switch (static_cast<int>(mInput->GetInputStates()[5])) {
	case 1:
		Rocket* rocket = new Rocket();
		GameObjectManager::GetInstance()->AddGameObject(rocket);
		rocket->AddParent(this);
		break;
	}
}

void SpaceShip::OnDestroy() { RELPTR(mTransform); }

void SpaceShip::OnCollision(GameObject* gt)
{

}
