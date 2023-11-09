#include "SkyBox.h"
#include "Engine/Component/Transform.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"

SkyBox::SkyBox() { }

SkyBox::~SkyBox() { }


void SkyBox::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, SKYBOX, L"Resources\\Assets\\spacemap.dds"));
	mTransform->SetScale(50000.f);
}

void SkyBox::OnUpdate(float deltaTime)
{
	mTransform->SetPosition(GameObjectManager::GetInstance()->GetCamera()->mTransform->GetWorldPosition());
}

void SkyBox::OnDestroy() { }

void SkyBox::OnCollision(GameObject* go) { }