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
	AddComponent<RenderComponent>(Engine::GetInstance()->mRenderManager->CreateRenderComponent(Engine::GetInstance()->mRenderManager->GetLosangeMesh()));
	AddComponent<Collider>(new Collider());
	AddComponent<Velocity>(new Velocity());
}

void Astero::OnUpdate(GameTimer* gt)
{
	//cout << "je suis là" << endl;
	//mTransform->Translate(0.01f, 0.0f, 0.0f);
	mTransform->Rotate(0.0f,1 * gt->DeltaTime(), 0.0f);
	mTransform->CalcWorldMatrix();
}

void Astero::OnDestroy(GameTimer* gt)
{
	//delete mItem;
	delete mTransform;
}
