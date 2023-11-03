#include "Component.h"
#include "Engine/GameObject.h"

Component::~Component() { RELPTR(mGameObject); }