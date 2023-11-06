#include "SkyBox.h"
#include "Engine/Component/Transform.h"

SkyBox::SkyBox() { }

void SkyBox::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SKYBOX, 5, L"Resources\\Assets\\spacemap.dds"));
	mTransform->SetScale(100, 100, 100);
}

void SkyBox::OnUpdate(float deltaTime)
{
}

void SkyBox::OnDestroy()
{
}

void SkyBox::OnCollision(GameObject* gt)
{

}