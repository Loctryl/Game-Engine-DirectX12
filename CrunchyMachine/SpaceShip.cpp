#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	RenderComponent* comp = new RenderComponent(QUAD, 0, L"Resources\\Assets\\box.dds", "First Texture");
	AddComponent<RenderComponent>(comp);

	//mTransform->Translate(2.0f,2.0f,2.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	//mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void SpaceShip::OnDestroy()
{
	delete mTransform;
}