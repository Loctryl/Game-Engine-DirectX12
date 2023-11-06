#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "States/DefaultState.h"
#include <random>


Astero::Astero() : GameObject()
{
	state = new DefaultState();
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

	int randomsize = 500;
	mTransform->Translate((float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100);
}

void Astero::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 1 * deltaTime);
}

void Astero::OnDestroy()
{
	delete mTransform;
}

void Astero::OnCollision(GameObject* go)
{
}
