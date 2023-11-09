#pragma once
#include "Particle.h"

enum EMIT_TYPE
{
	DIRECTIONAL,
	RADIAL,
};

// Defines a new particle spawner and manages them
class ParticleEmitter : public GameObject
{
private:
	vector<Particle*> mParticlePool;
	bool mIsRepeat;
	EMIT_TYPE mType;
	
public : 

	ParticleEmitter() = default;
	ParticleEmitter(EMIT_TYPE type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle = 0, float size = 0.2f, XMFLOAT3 position = XMFLOAT3(0,0,20));

	~ParticleEmitter() override;

	void OnInit() override;
	void OnUpdate(float deltaTime) override;
	void OnDestroy() override;
	void OnCollision(GameObject* go) override;

	void UpdateParticle(float deltaTime, Particle* particle);
	void RenewParticle(Particle* particle);
};

