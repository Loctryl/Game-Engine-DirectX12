#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit(GameTimer* gt)
{
	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetCubeMesh(), inst->GetShaderById(0)));

	mTransform->Translate(2.0f,2.0f,2.0f);
}

void SpaceShip::OnUpdate(GameTimer* gt)
{
	mTransform->Rotate(1 * gt->DeltaTime(), 1 * gt->DeltaTime(), 0.0f);
}

void SpaceShip::OnDestroy(GameTimer* gt)
{
	delete mTransform;
}