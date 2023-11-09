#include "UIElement.h"
#include "Engine/Component/Transform.h"

UIElement::UIElement() : GameObject()
{
	mPath = L"";
}

UIElement::UIElement(const wchar_t* path, string name, float divider) : GameObject()
{
	mPath = path;
	mTextureName = name;
	mDivider = divider;
}

void UIElement::OnInit()
{
	RenderComponent* comp = new RenderComponent(QUAD, ELEMENT_UI, mPath, mTextureName);

	comp->mIsDestructible = false;
	AddComponent<RenderComponent>(comp);
}

void UIElement::OnUpdate(float deltaTime) { }

void UIElement::OnDestroy() { }

void UIElement::OnCollision(GameObject* gt) { }