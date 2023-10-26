#include "Collider.h"

Collider::Collider()
{
}

Collider::Collider(float radius)
{
	mRadius = radius;
}

Collider::~Collider()
{
}

float Collider::GetRadius()
{
	return mRadius;
}
