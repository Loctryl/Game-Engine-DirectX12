#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(LOSANGE, 1));
	physics = new PhysicsComponent(mTransform, true, 1);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);
}

void Astero::OnUpdate(float deltaTime)
{

}

void Astero::OnDestroy()
{
	delete mTransform;
}

void Astero::OnCollision(GameObject* go)
{
}
