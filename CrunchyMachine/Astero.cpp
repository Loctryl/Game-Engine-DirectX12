#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"

Astero::Astero() : GameObject()
{

}

void Astero::OnInit()
{
	//RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(LOSANGE, 1));
	AddComponent<Collider>(new Collider());
	AddComponent<Velocity>(new Velocity());
}

void Astero::OnUpdate(float deltaTime)
{
	mTransform->Rotate(0.0f,1 * deltaTime, 0.0f);
}

void Astero::OnDestroy()
{
	delete mTransform;
}
