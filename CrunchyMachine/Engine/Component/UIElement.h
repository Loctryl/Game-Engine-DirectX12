#pragma once
#include "Engine/GameObject.h"

// Base UI Element that display a part of a texture, discarding black pixels in shader
class UIElement : public GameObject
{
private:
	virtual void OnInit() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void OnCollision(GameObject* gt) override;

	const wchar_t* mPath;
	string mTextureName;

public:
	UIElement();
	UIElement(const wchar_t* path, string name, float divider);
};