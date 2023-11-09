#include "Life.h"
#include "Engine/Component/UIElement.h"
#include "Engine/Component/Transform.h"


Life::Life(int maxLife) : GameObject()
{
	for (int i = 0; i < maxLife; i++) {
		mDigits.push_back(new UIElement(L"Resources\\Assets\\life.dds", "digit", 2));
		mDigits.back()->mDigit = 0;
		mDigits.back()->mTransform->SetScale(0.05f, 0.05f * RenderManager::GetAspectRatio(), 1.f);
		mDigits.back()->mTransform->SetPosition((i * 0.07f) - 0.85f, -0.8f, 0.06f);
	}
}

void Life::OnInit()
{

}

void Life::OnUpdate(float deltaTime)
{

}

void Life::OnDestroy()
{
}

void Life::OnCollision(GameObject* gt)
{
}

void Life::LooseLifeOnUI(int currLife)
{
	if(currLife >= 0)
		mDigits[currLife]->mDigit = 1;
}
