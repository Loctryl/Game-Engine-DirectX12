#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Resources/BitMask.h"

SpaceShip::SpaceShip() : GameObject()
{
	physics = nullptr;
}

void SpaceShip::OnInit(GameTimer* gt)
{
	mCountCollision = 0;

	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetCubeMesh(), inst->GetShaderById(0)));

	physics = new PhysicsComponent(mTransform, 1.0F);
	physics->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	//mTransform->SetPosition(0,0,0);

}

void SpaceShip::OnUpdate(GameTimer* gt)
{
	//mTransform->SetPosition(5 * std::cos(gt->TotalTime()), 0.0f, 0.0f);

	physics->SetVelocity(5 * std::cos(gt->TotalTime()), 0.0f, 0.0f);
}

void SpaceShip::OnDestroy(GameTimer* gt)
{
	delete mTransform;
}

void SpaceShip::OnCollision(GameObject* gt)
{
	mCountCollision++;
	cout << "collision : " << mCountCollision << endl;
}
