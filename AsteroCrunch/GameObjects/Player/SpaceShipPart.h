#pragma once
#include "Engine/GameObject.h"

// Composes the spaceship rendered items
// It's juste there to store RenderComponents set in spaceship
class SpaceShipPart : public GameObject
{
private:
	inline void OnInit() override { };
	inline void OnUpdate(float deltaTime) override { };
	inline void OnDestroy() override { };
	inline void OnCollision(GameObject* go) override { };

public:
	SpaceShipPart() = default;
	~SpaceShipPart() override = default;
};