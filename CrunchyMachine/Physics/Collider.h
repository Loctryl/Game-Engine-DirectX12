#pragma once
#include <iostream>
#include <vector>

class Collider {

public:
	Collider();
	~Collider();
	float GetRadius();

private:
	float mRadius;
	std::vector<std::wstring> mFlags;
};