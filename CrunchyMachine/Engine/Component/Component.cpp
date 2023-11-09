#include "Component.h"
#include "Engine/GameObject.h"

Component::~Component() { mGameObject = nullptr; }