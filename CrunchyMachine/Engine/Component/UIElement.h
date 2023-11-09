#pragma once
#include "Engine/GameObject.h"


class UIElement : public GameObject
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	const wchar_t* mPath;
	string mTextureName;

public:
	UIElement();
	UIElement(const wchar_t* path, string name, float divider);

};
