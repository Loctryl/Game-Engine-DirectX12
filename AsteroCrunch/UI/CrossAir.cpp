#include "CrossAir.h"

#include "Engine/Component/Transform.h"

CrossAir::CrossAir() : GameObject()
{

}

void CrossAir::OnInit()
{
    RenderComponent* comp = new RenderComponent(QUAD, STATIC_UI, L"Resources\\Assets\\crossAir.dds","crossAir");

    mDigit = 0;
    
    comp->mIsDestructible = false;
    AddComponent<RenderComponent>(comp);

    mTransform->SetScale(0.05f, 0.05f * RenderManager::GetAspectRatio(), 1.f);
    mTransform->SetPosition(0.f, 0.f, 0.06f);
}

void CrossAir::OnUpdate(float deltaTime)
{

}

void CrossAir::OnDestroy()
{
}

void CrossAir::OnCollision(GameObject* gt)
{
}
