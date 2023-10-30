#include "Astero.h"
#include "Transform.h"
#include "DirectX12/RenderComponent.h"
#include "GeoManager.h"
#include "Input.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit(GameTimer* gt)
{
	RenderManager* inst = RenderManager::GetInstance();

	mItem = inst->CreateRenderComponent(inst->GetLosangeMesh(), inst->GetShaderById(0));
	inst->gObj.push_back(this);
	mInput = new Input();
}

void Astero::OnUpdate(GameTimer* gt)
{
	mInput->UpdateArray();

	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 0:
		gt->ResetSlowMo();
		break;
	case 3:
		gt->IndentSlowMo();
		gt->SlowMotion(gt->SlowMoIndent());
		break;
	default:
		break;
	}


	mTransform->Rotate(0.0f,2 * gt->DeltaTime(), 0.0f);
	mTransform->CalcWorldMatrix();
}

void Astero::OnDestroy(GameTimer* gt)
{
	delete mItem;
	delete mTransform;
}
