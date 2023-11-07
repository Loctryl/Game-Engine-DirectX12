#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "States/DefaultState.h"
#include "GameObjects/SpaceShip/SpaceShipPart.h"
#include <random>


Astero::Astero() : GameObject()
{
	state = new DefaultState();
	mPartTest = new SpaceShipPart();
	mPartTest->AddParent(this);
	mPartTest->AddComponent<RenderComponent>(new RenderComponent(SPHERE, 2));
	mPartTest->mTransform->SetPosition(3.0f, 0.0f, 0.0f);
	mPartTest->mTransform->SetScale(0.3f, 0.3f, 0.3f);

}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(LOSANGE, 0));
	physics = new PhysicsComponent(mTransform, true, 1);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	StateMachineComponent* statemachine = new StateMachineComponent(state);
	AddComponent<StateMachineComponent>(statemachine);

}

void Astero::OnUpdate(float deltaTime)
{
	mTransform->Rotate(0, deltaTime, 0);
}

void Astero::OnDestroy()
{
}

void Astero::OnCollision(GameObject* go)
{

}
