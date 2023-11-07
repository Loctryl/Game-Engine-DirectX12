#include "UIElement.h"
#include "Engine/Component/Transform.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include <random>

UIElement::UIElement() : GameObject()
{
	numbersUV.push_back({ 0.0f,0.0f, });
	numbersUV.push_back({ 0.1f,0.0f, });
	numbersUV.push_back({ 0.0f,1.0f, });
	numbersUV.push_back({ 0.1f,1.0f, });

}

void UIElement::OnInit()
{
	RenderComponent* comp = new RenderComponent(SCORE, UI, L"Resources\\Assets\\numbers.dds","score");
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
