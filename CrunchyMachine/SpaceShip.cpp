#include "SpaceShip.h"
#include "Transform.h"
#include "DirectX12/RenderComponent.h"
#include "GeoManager.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit(GameTimer* gt)
{
	RenderManager* inst = RenderManager::GetInstance();

	mItem = inst->CreateRenderComponent(inst->GetCubeMesh(), inst->GetShaderById(0));
	inst->gObj.push_back(this);

	mTransform->Translate(2.0f,2.0f,2.0f);
}

void SpaceShip::OnUpdate(GameTimer* gt)
{
	//cout << "je suis là" << endl;
	//mTransform->Translate(0.01f, 0.0f, 0.0f);
	mTransform->Rotate(1 * gt->DeltaTime(), 1 * gt->DeltaTime(), 0.0f);
}

void SpaceShip::OnDestroy(GameTimer* gt)
{
	delete mItem;
	delete mTransform;
}