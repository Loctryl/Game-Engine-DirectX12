#include "Box.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

Box::Box() : GameObject()
{

}

void Box::OnInit()
{
	RenderComponent* comp = new RenderComponent(CUBE, 1, L"Resources\\Assets\\floor.dds", "Second one");
	AddComponent<RenderComponent>(comp);

	mTransform->SetPosition(-3.0f, 2.0f, 0.0f);
}

void Box::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void Box::OnDestroy()
{
	delete mTransform;
}