#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Component/RenderComponent.h"
#include "Resources/BitMask.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit(GameTimer* gt)
{
	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetLosangeMesh(), inst->GetShaderById(0)));

	PhysicsComponent* physics = new PhysicsComponent(mTransform, 1.0F);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);
}

void Astero::OnUpdate(GameTimer* gt)
{
	mTransform->Rotate(0.0f,1 * gt->DeltaTime(), 0.0f);
}

void Astero::OnDestroy(GameTimer* gt)
{
	//delete mItem;
	delete mTransform;
}

void Astero::OnCollision(GameObject* gt)
{
}
