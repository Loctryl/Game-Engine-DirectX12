#pragma once
#include <iostream>
#include <vector>
#include "Engine/Component/Component.h"

class Collider : public Component {

public:
	Collider();
	~Collider();
	float GetRadius();

private:
	float mRadius;
	std::vector<std::wstring> mFlags;
};