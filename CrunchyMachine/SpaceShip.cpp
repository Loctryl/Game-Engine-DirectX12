#include "SpaceShip.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"

SpaceShip::SpaceShip() : GameObject()
{

}

void SpaceShip::OnInit()
{
	RenderManager* inst = Engine::GetInstance()->mRenderManager;

	AddComponent<RenderComponent>(new RenderComponent(CUBE, 0, L"Resources\\Assets\\box.dds", "First Texture"));

	mTransform->Translate(2.0f,2.0f,2.0f);
}

void SpaceShip::OnUpdate(float deltaTime)
{
	mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
}

void SpaceShip::OnDestroy()
{
	delete mTransform;
}