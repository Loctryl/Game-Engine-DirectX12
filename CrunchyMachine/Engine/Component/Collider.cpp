#include "Collider.h"

Collider::Collider()
{
	mRadius = 0;
	mComponentType = COLLISION;
}

Collider::~Collider()
{
}

float Collider::GetRadius()
{
	return mRadius;
}
