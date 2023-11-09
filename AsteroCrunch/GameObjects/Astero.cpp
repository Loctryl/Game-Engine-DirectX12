#include "Astero.h"
#include "Engine/Component/Transform.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/Component/StateMachine/StateMachineComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/Engine.h"
#include "Engine/Input.h"
#include "EngineResources/Color.h"
#include <random>


Astero::Astero(XMFLOAT3 position, XMFLOAT4 quat, float speed) : Entity()
{
	mTransform->SetPosition(position);
	mTransform->SetRotation(quat);
	mTransform->RotateOnAxis(0, 1, 0, 180); //make it face the player
	mSpeed = speed;

	mId->SetMask(2);
	mId->SetMask(0);
}

Astero::~Astero()
{
}

void Astero::OnInit()
{
	float scale = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (_countof(mTextures) - 1)));

	AddComponent<RenderComponent>(new RenderComponent(SPHERE, LITTEXTURE, mTextures[(int)round(scale)]));
	GetComponent<RenderComponent>(RENDER)->SetColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f));

	scale++;
	InitMaxHp(round(scale));
	scale = pow(scale, 2) * 3;

	physics = new PhysicsComponent(mTransform, true, scale);
	physics->SetMask(1);
	physics->SetMask(2);
	AddComponent<PhysicsComponent>(physics);

	mTransform->SetScale(scale);
	XMFLOAT3 dirz = mTransform->GetDirz();
	XMVECTOR velocity = XMLoadFloat3(&dirz) * mSpeed;
	XMStoreFloat3(&dirz, velocity);
	physics->AddVelocity(dirz);
}

void Astero::OnUpdate(float deltaTime)
{

}

void Astero::OnDestroy()
{
}

void Astero::OnCollision(GameObject* go)
{
	cout << "detected" << endl;
	if (go->mId->IsBitMask(0)) {
		cout << "boom" << endl;
		ToDestroy = true;
	}
}
