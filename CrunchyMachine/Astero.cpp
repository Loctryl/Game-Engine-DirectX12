#include "Astero.h"
#include "Transform.h"
#include "DirectX12/RenderComponent.h"
#include "GeoManager.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit(GameTimer* gt)
{
	mItem = GeoManager::GetInstance()->CreateRenderComponent(GeoManager::GetInstance()->GetLosangeMesh());
	GeoManager::GetInstance()->gObj.push_back(this);
}

void Astero::OnUpdate(GameTimer* gt)
{
	//cout << "je suis là" << endl;
	mTransform->Translate(0.01f, 0.0f, 0.0f);
	mTransform->Rotate(0.01f, 0.0f, 0.0f);
	mTransform->CalcWorldMatrix();
}

void Astero::OnDestroy(GameTimer* gt)
{
	delete mItem;
	delete mTransform;
}
