#pragma once
#include <iostream>
#include <vector>

class GameObject;

class CollisionManager {

public:
	CollisionManager();
	~CollisionManager();

	static CollisionManager* GetInstance();

	void Update();

private:
	static CollisionManager* mInstance;
	std::vector<GameObject*> mColliderObjects;
};