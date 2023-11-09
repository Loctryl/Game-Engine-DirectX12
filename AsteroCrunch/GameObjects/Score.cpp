#include "Score.h"
#include "Engine/Component/UIDigit.h"
#include "Engine/Component/Transform.h"


Score::Score() : GameObject()
{
	for (int i = 0; i < 8; i++) {
		mDigits.push_back(new UIDigit());
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
	mScore++;
	SetDigits(mScore);
}

void Score::OnDestroy()
{
}

void Score::OnCollision(GameObject* gt)
{
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
