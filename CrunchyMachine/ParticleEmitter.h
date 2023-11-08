#pragma once
#include "Particle.h"

class ParticleEmitter : public GameObject
{
public : 
	enum class EmitType
	{
		DIRECTIONAL,
		RADIAL,
	};

	ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size, XMFLOAT3 position);
	ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size);
	ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle);
	ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color);

	void virtual OnInit() override;
	void virtual OnUpdate(float deltaTime) override;
	void virtual OnDestroy() override;
	void virtual OnCollision(GameObject* gt) override;

	void ReturnParticleToPool(Particle* deadParticle);
	Particle* FetchDeadParticle();
	void UpdateParticle(float deltaTime, Particle* particle);
	void AddParticle();

private:
	std::vector<Particle*> mParticlePool;
	int mAliveParticleCount;
	EmitType mType;
	bool mIsActive;
};

