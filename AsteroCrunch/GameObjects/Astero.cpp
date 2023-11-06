#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "States/DefaultState.h"

Astero::Astero() : Script()
{
	state = new DefaultState();
}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	mGameObject->AddComponent<RenderComponent>(new RenderComponent(LOSANGE, 1));
	physics = new PhysicsComponent(mGameObject->mTransform, true, 1);
	physics->SetMask(1);
	mGameObject->AddComponent<PhysicsComponent>(physics);

	StateMachineComponent* statemachine = new StateMachineComponent(state);
	mGameObject->AddComponent<StateMachineComponent>(statemachine);
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
