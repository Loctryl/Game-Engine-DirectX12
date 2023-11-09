#include "UIDigit.h"
#include "Engine/Component/Transform.h"

UIDigit::UIDigit() : GameObject()
{

}

void UIDigit::OnInit()
{
	RenderComponent* comp = new RenderComponent(QUAD, DIGITUI, L"Resources\\Assets\\numbers.dds","digit");
	//comp->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

	comp->mIsDestructible = false;
	AddComponent<RenderComponent>(comp);
}

void UIDigit::OnUpdate(float deltaTime)
{

}

void UIDigit::OnDestroy()
{
}

void UIDigit::OnCollision(GameObject* gt)
{
}
