#include "CollisionGrid.h"
#include "Engine/Component/PhysicsComponent.h"

CollisionGrid::CollisionGrid(int x, int y, int z)
{
	mPosition = { x, y, z };
}

CollisionGrid::~CollisionGrid()
{
	for (auto obj : mObjects)
		delete obj;

	mObjects.clear();
}
