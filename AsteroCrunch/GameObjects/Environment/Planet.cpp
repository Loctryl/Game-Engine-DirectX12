#include "Planet.h"
#include "Engine/Component/Transform.h"
#include "Resources/framework.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"

Planet::Planet(int texIndex, XMFLOAT3 position, float scale) : GameObject()
{
	mTransform->SetScale(scale);
	mTransform->SetPosition(position);
	mId->SetMask(PLANETE);
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, LIT_TEXTURE, mTextures[texIndex%5]));
}

void Planet::OnInit() { }

void Planet::OnUpdate(float deltaTime)
{
	XMFLOAT3 camPos = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetWorldPosition();
	XMFLOAT3 pos = mTransform->GetWorldPosition();

	//Making them "respawn" if too far to save memory
	if (std::abs(pos.z - camPos.z) >= KILLBOX/2 -50)
	{
		int maxScale = 75;
		int minScale = 35;
		float scale = rand() % (maxScale - minScale + 1) + maxScale;

		int xmax = 1000;
		int xmin = BORDER_SIZE + scale;
		float xPos = rand() % (xmax - xmin + 1) + xmin;
		if (rand() % 2 == 1) xPos *= -1;

		int zmax = 1000;
		float zPos = rand() % zmax + 1000;

		XMFLOAT3 position = XMFLOAT3(xPos + camPos.y, 0, zPos + camPos.z);
		
		mTransform->SetPosition(position);
		mTransform->SetScale(scale);
	}
}

void Planet::OnDestroy() { }

void Planet::OnCollision(GameObject* go) { }