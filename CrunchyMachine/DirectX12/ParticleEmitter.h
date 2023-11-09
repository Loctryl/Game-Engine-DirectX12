#pragma once
#include "Particle.h"

enum EmitType
{
	DIRECTIONAL,
	RADIAL,
};

class ParticleEmitter : public GameObject
{
public : 

	ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle = 0, float size = 1, XMFLOAT3 position = XMFLOAT3(0,0,20));

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void UpdateParticle(float deltaTime, Particle* particle);
	void RenewParticle(Particle* particle);

private:
	std::vector<Particle*> mParticlePool;
	int mAliveParticleCount;
	bool mIsRepeat;
};

