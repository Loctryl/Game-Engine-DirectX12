#include "ParticleEmitter.h"
#include "Engine/Component/Transform.h"
#include <random>

ParticleEmitter::ParticleEmitter(EMIT_TYPE type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size, XMFLOAT3 position)
{
	mTransform->SetPosition(position);

	switch (type)
	{
	case DIRECTIONAL:
		break;
	case RADIAL:
		for (int i = 0; i < particleCount; i++)
		{
			int random = rand();

			XMFLOAT3 tempVelocity;
			XMStoreFloat3(&tempVelocity, XMLoadFloat3(&velocity) * (random % 9 / 2.6f + 0.2f));
			angle = random % 360;
			size = random % 3 / 1.8f + 1.5;
			float tempLifeTime = lifetime * (random % 4 / 2.2f + 0.2f);

			mParticlePool.push_back(new Particle(i, tempVelocity, tempLifeTime, color, angle, size, position));
			srand(i * (time(0) % 40 / 1.6));
		}
		mIsRepeat = true;
		break;
	default:
		break;
	}
}

void ParticleEmitter::OnInit() { }

void ParticleEmitter::OnUpdate(float deltaTime)
{
	for (int i = 0; i < mParticlePool.size(); i++)
	{
		Particle* tempParticle = mParticlePool[i];
		assert(tempParticle);
		UpdateParticle(deltaTime, tempParticle);
	}
}

void ParticleEmitter::OnDestroy() { }

void ParticleEmitter::OnCollision(GameObject* gt) { }

void ParticleEmitter::UpdateParticle(float deltaTime, Particle* particle)
{
	if (particle == nullptr) 
	{
		return;
	}

	//particle->SetLifeTime(particle->GetLifeTime() - deltaTime);


	if (particle->GetLifeTime() > 0)
	{
		//float AgeRatio = particle->GetLifeTime() / particle->GetOriginLifeTime();
		//particle->SetSize(particle->GetOriginSize() * AgeRatio);

		//particle->mTransform->Translate(XMFLOAT3(particle->GetPhysics()->GetVelocity().x * deltaTime, particle->GetPhysics()->GetVelocity().y * deltaTime, 0));
		//particle->mTransform->GetPosition();
	}
	else
	{
		RenewParticle(particle);
	}
}

void ParticleEmitter::RenewParticle(Particle* particle)
{
	if (particle == nullptr || particle->GetIndex() < 0) 
		return;

	if (mIsRepeat) 
	{
		XMFLOAT3 tempPosition = mTransform->GetPosition();
		particle->mTransform->GetPosition();
		//particle->mTransform->SetPosition(tempPosition);
		//particle->SetSize(particle->GetOriginSize());
		//particle->SetLifeTime(particle->GetOriginLifeTime());
	}
	else 
	{
		particle->mToDestroy = true;
		mParticlePool[particle->GetIndex()] = nullptr;
	}
}