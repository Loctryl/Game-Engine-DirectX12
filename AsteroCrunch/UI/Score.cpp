#include "Score.h"
#include "Engine/Component/UIElement.h"
#include "Engine/Component/Transform.h"


Score::Score() : GameObject()
{
	for (int i = 0; i < 8; i++) {
		mDigits.push_back(new UIElement(L"Resources\\Assets\\numbers.dds", "digit", 10));
		mDigits.back()->mTransform->SetScale(0.03f, 0.03f *RenderManager::GetAspectRatio(), 1.f);
		mDigits.back()->mTransform->SetPosition((i*0.07f) - 0.25f, 0.9f, 0.06f);
	}
}

void Score::OnInit()
{
	//mTransform->SetScale(0.2f, 0.2f, 0.2f);
}

void Score::OnUpdate(float deltaTime)
{
	mFloatScore += deltaTime * 10;
	mScore += floor(mFloatScore);

	if (mFloatScore >= 1) mFloatScore = 0;

	SetDigits(mScore);
}

void Score::OnDestroy()
{
}

void Score::OnCollision(GameObject* gt)
{
}

void Score::AddScore(int qty)
{
	mScore += qty;
	SetDigits(mScore);
}

void Score::SetDigits(int num)
{
	int score = mScore;
	int divide = 10000000;
	for (int i = 0; i < 8; i++)
	{
		int v = score / divide;
		mDigits[i]->mDigit = v;
		score -= v * divide;
		divide /= 10;
	}
}
