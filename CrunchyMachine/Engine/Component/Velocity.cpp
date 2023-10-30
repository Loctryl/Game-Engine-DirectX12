#include "Velocity.h"

Velocity::Velocity()
{
	mComponentType = VELOCITY;
}

Velocity::Velocity(XMFLOAT3* position)
{
}

void Velocity::SetVelocity(XMFLOAT3 velocity)
{
	mVelocity = velocity;
}

void Velocity::SetVelocity(float x, float y, float z)
{
	mVelocity = { x, y , z };
}
