#include "Component.h"

Component::~Component()
{
	delete mGameObject;
}
