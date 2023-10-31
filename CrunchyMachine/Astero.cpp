#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit(GameTimer* gt)
{
	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetSphereMesh(), inst->GetShaderById(0)));
	AddComponent<Collider>(new Collider());
	AddComponent<Velocity>(new Velocity());
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
