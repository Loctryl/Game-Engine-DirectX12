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

	void AddFlag(std::wstring flag);
	void ClearObjects();

private:
	static CollisionManager* mInstance;
	std::vector<GameObject*> mColliderObjects;
	std::vector<std::wstring> mFlagsCollection;
};