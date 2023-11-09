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
	~Particle() override;

	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* gt) override;

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