#include "ParticleEmitter.h"
#include "Engine/Component/Transform.h"
#include <random>

ParticleEmitter::ParticleEmitter(EmitType type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size, XMFLOAT3 position)
{
	mType = type;
	mParticlePool.reserve(particleCount);
	mAliveParticleCount = -1;
	for (int i = 0; i < particleCount; i++)
	{
		mParticlePool.push_back(new Particle(i, velocity, lifetime, color, angle, size, position));
	}
	mIsActive = true;
}

void ParticleEmitter::OnInit()
{
}

void ParticleEmitter::OnUpdate(float deltaTime)
{
	while (mIsActive)
	{
		AddParticle();
	}

	for (int i = 0; i < mParticlePool.size(); i++)
	{
		Particle* tempParticle = mParticlePool[i];
		UpdateParticle(deltaTime, tempParticle);
	}
}

void ParticleEmitter::OnDestroy()
{
}

void ParticleEmitter::OnCollision(GameObject* gt)
{
}

void ParticleEmitter::ReturnParticleToPool(Particle* deadParticle)
{
	//Get Alive Particle ref
	Particle* aliveParticle = mParticlePool[mAliveParticleCount];

	//Attribute dead particule to alive particule slot
	mParticlePool[mAliveParticleCount] = deadParticle;
	//Attribute alive particule to dead particule slot
	mParticlePool[deadParticle->GetIndex()] = aliveParticle;

	//Set alive particle index to dead particle index
	aliveParticle->SetIndex(deadParticle->GetIndex());
	//Set dead particule index to alive particle old index
	deadParticle->SetIndex(mAliveParticleCount);

	//Decrement total alive particle count
	mAliveParticleCount--;
}

Particle* ParticleEmitter::FetchDeadParticle()
{
	if (mAliveParticleCount + 1 > mParticlePool.size())
		return nullptr;

	return mParticlePool[mAliveParticleCount + 1];
}

void ParticleEmitter::UpdateParticle(float deltaTime, Particle* particle)
{
	particle->SetLifeTime(particle->GetLifeTime() - deltaTime);

	if (particle->GetLifeTime() > 0)
	{
		float AgeRatio = particle->GetLifeTime() / particle->GetOriginLifeTime();
		particle->SetSize(particle->GetOriginSize() * AgeRatio);

		particle->mTransform->Translate(XMFLOAT3(particle->GetPhysics()->GetVelocity().x * deltaTime, particle->GetPhysics()->GetVelocity().y * deltaTime, 0));
	}
	else
	{
		particle->SetIsAlive(false);
		ReturnParticleToPool(particle);
	}
}

void ParticleEmitter::AddParticle()
{
	if (FetchDeadParticle() != nullptr) 
	{
		Particle* tempParticle = FetchDeadParticle();
		mAliveParticleCount++;
		mParticlePool[mAliveParticleCount] = tempParticle;
	}
	else 
	{
		return;
	}
}
