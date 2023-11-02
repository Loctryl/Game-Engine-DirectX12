#include "Box.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

Box::Box() : GameObject()
{

}

void Box::OnInit()
{
	RenderComponent* comp = new RenderComponent(CUBE, 0, L"Resources\\Assets\\box.dds", "Second one");
	AddComponent<RenderComponent>(comp);

	mTransform->SetPosition(-3.0f, 2.0f, 0.0f);

}

void Box::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
	//mTransform->Rotate(-1 * deltaTime / 3, 0.0f, 0.0f);


}

void Box::OnDestroy()
{
	delete mTransform;
}