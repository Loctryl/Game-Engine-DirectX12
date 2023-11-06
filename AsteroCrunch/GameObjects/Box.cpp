#include "Box.h"
#include "Engine/Component/Transform.h"
#include "Engine/GameObject.h"
#include "Engine/Engine.h"
#include "Engine/Component/PhysicsComponent.h"
#include <random>

Box::Box() : Script()
{

}

void Box::OnInit()
{
	RenderComponent* comp = new RenderComponent(SPHERE, 1);
	mGameObject->AddComponent<RenderComponent>(comp);
	PhysicsComponent* physics = new PhysicsComponent(mGameObject->mTransform, true, 2);
	physics->SetMask(1);
	mGameObject->AddComponent<PhysicsComponent>(physics);

	int randomsize = 800;
	mGameObject->mTransform->Translate((float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100, (float)(rand() % randomsize) / 100);

}

void Box::OnUpdate(float deltaTime)
{
	mGameObject->mTransform->Rotate(1 * deltaTime, 1 * deltaTime, 0.0f);
	//mTransform->Rotate(-1 * deltaTime / 3, 0.0f, 0.0f);


}

void Box::OnDestroy()
{
}

void Box::OnCollision(GameObject* gt)
{
}
