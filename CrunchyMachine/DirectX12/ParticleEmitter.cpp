#include "ParticleEmitter.h"
#include "Engine/Component/Transform.h"
#include <random>

ParticleEmitter::ParticleEmitter(EMIT_TYPE type, int particleCount, XMFLOAT3 velocity, float lifetime, XMFLOAT4 color, float angle, float size, XMFLOAT3 position)
{
	mTransform->SetPosition(position);

	mType = type;

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
			float tempAngle = random % 360;
			float tempSize = size * (random % 4 * 0.3 + 1);
			float tempLifeTime = lifetime * (random % 4 * 0.3 + 1);

			mParticlePool.push_back(new Particle(i, tempVelocity, tempLifeTime, color, tempAngle, tempSize, position));
			srand(i * (time(0) % 40 / 1.6));
		}
		mIsRepeat = false;
		break;
	default:
		break;
	}
}

ParticleEmitter::~ParticleEmitter()
{
	for(auto obj : mParticlePool)
		obj->mToDestroy = true;
	mParticlePool.clear();
}

void ParticleEmitter::OnInit() { }

void ParticleEmitter::OnUpdate(float deltaTime)
{
	for (int i = 0; i < mParticlePool.size(); i++)
	{
		Particle* tempParticle = mParticlePool[i];
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

	particle->SetLifeTime(particle->GetLifeTime() - deltaTime);


	if (particle->GetLifeTime() > 0)
	{
		float AgeRatio = particle->GetLifeTime() / particle->GetOriginLifeTime();
		particle->SetSize(particle->GetOriginSize() * AgeRatio);

		particle->mTransform->Translate(XMFLOAT3(particle->GetPhysics()->GetVelocity().x * deltaTime, particle->GetPhysics()->GetVelocity().y * deltaTime, 0));
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
		//particle->mTransform->GetPosition();
		particle->mTransform->SetPosition(tempPosition);
		particle->SetSize(particle->GetOriginSize());
		particle->SetLifeTime(particle->GetOriginLifeTime());
	}
	else 
	{
		int tempIndex = particle->GetIndex();
		particle->mToDestroy = true;
		mParticlePool[tempIndex] = nullptr;
		if (tempIndex == mParticlePool.size() - 1) 
			mToDestroy = true;
	}
}