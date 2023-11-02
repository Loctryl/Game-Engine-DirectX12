#pragma once
#include "Resources/PhysicsRessources.h"
#include <vector>
#include "Resources/framework.h"

class PhysicsComponent;

class CollisionGrid
{
public:
	CollisionGrid(int x, int y, int z);
	~CollisionGrid();

private:
	std::vector<PhysicsComponent*> mObjects;
	XMFLOAT3 mPosition;
};