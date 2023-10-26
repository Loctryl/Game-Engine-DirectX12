#pragma once
#include <iostream>
#include <vector>

class GameObject;

class VelocityManager {

public:
	VelocityManager();
	~VelocityManager();

	static VelocityManager* GetInstance();

	void Update();

private:

	static VelocityManager* mInstance;
	std::vector<GameObject*> mVelocityObjects;
};