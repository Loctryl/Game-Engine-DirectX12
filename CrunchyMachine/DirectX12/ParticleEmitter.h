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
public : 

	ParticleEmitter() = default;
	ParticleEmitter(EMIT_TYPE type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle = 0, float size = 0.2f, XMFLOAT3 position = XMFLOAT3(0,0,20));

	~ParticleEmitter() = default;

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void UpdateParticle(float deltaTime, Particle* particle);
	void RenewParticle(Particle* particle);

private:
	std::vector<Particle*> mParticlePool;
	bool mIsRepeat;
};

