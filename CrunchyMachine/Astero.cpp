#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"

Astero::Astero() : GameObject()
{
	mInput = Input::GetInstance();
}

void Astero::OnInit(GameTimer* gt)
{
	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(inst->CreateRenderComponent(inst->GetLosangeMesh(), inst->GetShaderById(0)));
	AddComponent<Collider>(new Collider());
	AddComponent<Velocity>(new Velocity());
}

void Astero::OnUpdate(GameTimer* gt)
{
<<<<<<< Updated upstream
	mTransform->Rotate(0.0f,1 * gt->DeltaTime(), 0.0f);
=======
	switch (static_cast<int>(mInput->GetInputStates()[0])) {
	case 3:
		mTransform->Translate(0, 0, 1 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[1])) {
	case 3:
		mTransform->Translate(-1 * deltaTime, 0, 0);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[2])) {
	case 3:
		mTransform->Translate(0, 0, -1 * deltaTime);
		break;
	default:
		break;
	}
	switch (static_cast<int>(mInput->GetInputStates()[3])) {
	case 3:
		mTransform->Translate(1 * deltaTime, 0, 0);
		break;
	default:
		break;
	}


>>>>>>> Stashed changes
}

void Astero::OnDestroy(GameTimer* gt)
{
	//delete mItem;
	delete mTransform;
}
