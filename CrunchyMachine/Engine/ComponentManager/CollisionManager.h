#pragma once
#include <iostream>
#include <vector>
#include "Engine/ComponentManager/ComponentManager.h"
#include "Engine/Component/Collider.h"

class CollisionManager : public ComponentManager<Collider>{

public:
	CollisionManager();
	~CollisionManager();

	void Update();

	void AddFlag(std::wstring flag);

private:
	std::vector<std::wstring> mFlagsCollection;
};