#include "UIElement.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include <random>

UIElement::UIElement() : GameObject()
{
	//numbersUV.push_back({0.f,0.1f,})
}

void UIElement::OnInit()
{
	RenderComponent* comp = new RenderComponent(QUAD, UI);
	//comp->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));
	AddComponent<RenderComponent>(comp);
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
