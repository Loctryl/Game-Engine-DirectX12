#include "Planet.h"
#include "Engine/Component/Transform.h"
#include "Resources/framework.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Resources/framework.h"

Planet::Planet(int texIndice, XMFLOAT3 position, float scale) : GameObject()
{
	mTransform->SetScale(scale);
	mTransform->SetPosition(position);
	mId->SetMask(PLANETE);
}

void Planet::OnInit()
{
	AddComponent<RenderComponent>(new RenderComponent(SPHERE, LIT_TEXTURE, L"Resources//Assets//AsteroTex//asteroTex1.dds"));
}

void Planet::OnUpdate(float deltaTime)
{
	XMFLOAT3 camPos = GameObjectManager::GetInstance()->GetCamera()->mTransform->GetWorldPosition();
	XMFLOAT3 pos = mTransform->GetWorldPosition();

	cout << "lul" << endl;

	if (std::abs(pos.x - camPos.x) >= KILLBOX -100 ||
		std::abs(pos.y - camPos.y) >= KILLBOX -100 ||
		std::abs(pos.z - camPos.z) >= KILLBOX -100 
		)
	{
		int maxScale = 75;
		int minScale = 35;
		float scale = rand() % (maxScale - minScale + 1) + maxScale;

		int xmax = 1000;
		int xmin = BORDER_SIZE + scale;
		float xPos = rand() % (xmax - xmin + 1) + xmin;
		if (rand() % 2 == 1) xPos *= -1;

		int zmax = 1000;
		float zPos = rand() % zmax;

		XMFLOAT3 position = XMFLOAT3(xPos, 0, zPos);

		mTransform->SetPosition(position);
		mTransform->SetScale(scale);
		cout << position.x << " , " << position.y << " , " << position.z << endl;
	}
}

void Planet::OnDestroy()
{
}

void Planet::OnCollision(GameObject* gt)
{
}

Planet::~Planet() {

}