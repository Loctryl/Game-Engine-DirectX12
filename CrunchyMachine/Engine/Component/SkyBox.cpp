#include "SkyBox.h"
#include "Engine/Component/Transform.h"

SkyBox::SkyBox() { }

void SkyBox::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, SKYBOX, L"Resources\\Assets\\spacemap.dds"));
	mTransform->SetScale(1400.f);
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