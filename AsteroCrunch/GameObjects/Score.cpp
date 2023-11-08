#include "Score.h"
#include "Engine/Component/UIElement.h"
#include "Engine/Component/Transform.h"


Score::Score() : GameObject()
{
	for (int i = 0; i < 8; i++) {
		mDigits.push_back(new UIElement());
		mDigits.back()->mTransform->SetPosition((i*2), 0, 1);
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
