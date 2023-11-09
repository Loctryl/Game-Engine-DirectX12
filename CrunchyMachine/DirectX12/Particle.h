#pragma once
#include "Engine/GameObject.h"

// Object used in ParticlesEmitter
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
	~Particle() override = default;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	float GetIndex() const;
	void SetIndex(float index);
	
	float GetOriginLifeTime() const;
	void SetOriginLifeTime(float value);
	
	float GetLifeTime() const;
	void SetLifeTime(float value);
	
	float GetOriginSize() const;
	void SetOriginSize(float value);
	
	float GetSize() const;
	void SetSize(float value);
	
	XMFLOAT4 GetColor() const;
	void SetColor(XMFLOAT4 color);
	
	PhysicsComponent* GetPhysics() const;
};

