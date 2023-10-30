#include "Astero.h"
#include "Transform.h"
#include "DirectX12/RenderComponent.h"
#include "GeoManager.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit(GameTimer* gt)
{
	RenderManager* inst = RenderManager::GetInstance();

	mItem = inst->CreateRenderComponent(inst->GetLosangeMesh(), inst->GetShaderById(0));
	inst->gObj.push_back(this);
}

void Astero::OnUpdate(GameTimer* gt)
{
	mTransform->Rotate(0.0f,1 * gt->DeltaTime(), 0.0f);
}

void Astero::OnDestroy(GameTimer* gt)
{
	delete mItem;
	delete mTransform;
}
