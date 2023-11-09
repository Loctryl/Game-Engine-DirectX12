#pragma once
#include "Entity.h"

class PhysicsComponent;

class Astero : public Entity
{
	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

public:

	Astero(XMFLOAT3 position, XMFLOAT4 quat, float speed);
	~Astero();

private:
	PhysicsComponent* physics;
	float mSpeed;
	float mMaxScale = 3;

	const wchar_t* mTextures[3]{
		L"Resources//Assets//AsteroTex//asteroTex1.dds",
		L"Resources//Assets//AsteroTex//asteroTex2.dds",
		L"Resources//Assets//AsteroTex//asteroTex3.dds"
	};

};

