#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"


Astero::Astero(GameObject* parent , float speed) : GameObject()
{
	mParent = parent;
	mTransform->SetRotation(mParent->mTransform->GetRotation());
	mTransform->SetPosition(mParent->mTransform->GetPosition());
}

void Astero::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(CUBE, 0));
	physics = new PhysicsComponent(mTransform, true, 1);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

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
