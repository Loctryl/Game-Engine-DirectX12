#pragma once
#include "Engine/GameObject.h"

class Particle : public GameObject
{
private:
	float mIndex;
	float mOriginLifetime;
	float mLifetime;
	float mOriginSize;
	float mSize;
	XMFLOAT4 mColor;

	PhysicsComponent* mPhysics;
	RenderComponent* mRender;

public:
	Particle(float index, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size, XMFLOAT3 position);
	~Particle();

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	float GetIndex();
	void SetIndex(float index);
	float GetOriginLifeTime();
	void SetOriginLifeTime(float value);
	float GetLifeTime();
	void SetLifeTime(float value);
	float GetOriginSize();
	void SetOriginSize(float value);
	float GetSize();
	void SetSize(float value);
	XMFLOAT4 GetColor();
	void SetColor(XMFLOAT4 color);
	PhysicsComponent* GetPhysics();
};

