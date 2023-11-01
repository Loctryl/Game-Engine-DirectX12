#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Resources/BitMask.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit(GameTimer* gt)
{
	mCountCollision = 0;

	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetCubeMesh(), inst->GetShaderById(0)));

	PhysicsComponent* physics = new PhysicsComponent(mTransform, 1.0F);
	physics->GetBitMask()->SetMask(1);
	AddComponent<PhysicsComponent>(physics);

	//mTransform->SetPosition(0,0,0);

}

void SpaceShip::OnUpdate(GameTimer* gt)
{
	//cout << "je suis là" << endl;
	//mTransform->Translate(0.01f, 0.0f, 0.0f);
	mTransform->SetPosition(5 * std::cos(gt->TotalTime()), 0.0f, 0.0f);
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
