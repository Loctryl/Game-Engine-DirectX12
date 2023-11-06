#include "SkyBox.h"

SkyBox::SkyBox() { }

void SkyBox::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SKYBOX, 5, L"Resources\\Assets\\spacebox.dds"));
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