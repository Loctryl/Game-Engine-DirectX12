#include "ElCubo.h"
#include "Engine/Component/Transform.h"

ElCubo::ElCubo() : GameObject()
{

}

void ElCubo::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(LOSANGE, 1));
	AddComponent<Collider>(new Collider());
	AddComponent<Velocity>(new Velocity());
}

void ElCubo::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void ElCubo::OnDestroy()
{
	delete mTransform;
}