#include "Border.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Component/RenderComponent.h"
#include "Resources/framework.h"

Border::Border() : GameObject()
{
	mPhysic = nullptr;
}

Border::~Border() {	mPhysic = nullptr; }

void Border::OnInit()
{
	mPhysic = new PhysicsComponent(mTransform, true, 2, true);
	mPhysic->SetMask(BORDER);
	AddComponent<PhysicsComponent>(mPhysic);

	/*RenderComponent* cube = new RenderComponent(SPHERE, LITCOLOR);
	cube->SetColor(XMFLOAT4(1.f, 0.f, 0.f, 1.f));
	AddComponent<RenderComponent>(cube);*/
}

void Border::OnUpdate(float deltaTime) { }

void Border::OnDestroy() { }

void Border::OnCollision(GameObject* go) { }