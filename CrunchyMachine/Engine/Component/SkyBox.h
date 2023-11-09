#pragma once
#include "Engine/GameObject.h"

// Unique sky box to display
class SkyBox : public GameObject
{
private:
	virtual void OnInit() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDestroy() override;
	virtual void OnCollision(GameObject* gt) override;

public:
	SkyBox();
	~SkyBox() override;
};