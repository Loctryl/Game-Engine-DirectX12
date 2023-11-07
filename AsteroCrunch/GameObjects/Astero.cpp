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


Astero::Astero() : GameObject()
{
	state = new DefaultState();
}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(LOSANGE));
	GetComponent<RenderComponent>(RENDER)->SetColor(Color::cyan());
	physics = new PhysicsComponent(mTransform, true, 1);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	StateMachineComponent* statemachine = new StateMachineComponent(state);
	AddComponent<StateMachineComponent>(statemachine);

}

void Astero::OnUpdate(float deltaTime)
{
	mTransform->Rotate(0.0f, 1 * deltaTime, 0.0f);
}

void Astero::OnDestroy()
{
}

void Astero::OnCollision(GameObject* go)
{

}
