#include "Border.h"
#include "Engine/Component/PhysicsComponent.h"
#include "Engine/Component/RenderComponent.h"

void Border::OnInit()
{
	physics = new PhysicsComponent(mTransform, true, 2, true);
	physics->SetMask(5);
	AddComponent<PhysicsComponent>(physics);

	/*RenderComponent* cube = new RenderComponent(SPHERE, LITCOLOR);
	cube->SetColor(XMFLOAT4(1.f, 0.f, 0.f, 1.f));
	AddComponent<RenderComponent>(cube);*/
}

void Border::OnUpdate(float deltaTime)
{
}

void Border::OnDestroy()
{
}

void Border::OnCollision(GameObject* gt)
{
}

Border::Border()
{
}

Border::~Border()
{
}
