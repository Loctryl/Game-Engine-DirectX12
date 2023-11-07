#include "SkyBox.h"
#include "Engine/Component/Transform.h"

SkyBox::SkyBox() { }

void SkyBox::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SKYBOX, 5, L"Resources\\Assets\\spacemap.dds"));
	mTransform->SetScale(200.f, 200.f, 200.f);
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