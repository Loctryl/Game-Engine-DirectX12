#include "UIElement.h"
#include "Engine/Component/Transform.h"

UIElement::UIElement() : GameObject()
{

}

void UIElement::OnInit()
{
	RenderComponent* comp = new RenderComponent(QUAD, UI, L"Resources\\Assets\\numbers.dds","digit");
	//comp->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
	AddComponent<RenderComponent>(comp);
	mTransform->SetScale(0.2f, 0.2f, 0.2f);
}

void UIElement::OnUpdate(float deltaTime)
{

}

void UIElement::OnDestroy()
{
}

void UIElement::OnCollision(GameObject* gt)
{
}
