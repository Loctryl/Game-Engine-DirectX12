﻿#pragma once
#include "Engine/GameObject.h"

class CrossAir : public  GameObject
{
    void virtual OnInit() override;
    void virtual OnUpdate(float deltaTime) override;
    void virtual OnDestroy() override;
    void virtual OnCollision(GameObject* gt) override;

public:
    CrossAir();
};

