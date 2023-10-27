#include "Collider.h"

Collider::Collider()
{
	mRadius = 0;
	mComponentType = collision;
}

Collider::~Collider()
{
}

float Collider::GetRadius()
{
	return mRadius;
}
