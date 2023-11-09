#pragma once
#include "GameObjects/Entity.h"

class PhysicsComponent;

// Obstacle entities that came in front of the player
class Astero : public Entity
{
private:
	PhysicsComponent* mPhysic;
	float mSpeed;
	float mMaxScale = 3;

	const wchar_t* mTextures[3]{
		L"Resources\\Assets\\AsteroTex\\asteroTex1.dds",
		L"Resources\\Assets\\AsteroTex\\asteroTex2.dds",
		L"Resources\\Assets\\AsteroTex\\asteroTex3.dds"
	};
	
	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

public:
	Astero(XMFLOAT3 position, XMFLOAT4 quat, float speed);
	~Astero() override;
};

