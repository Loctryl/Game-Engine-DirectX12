#pragma once
#include "Engine/Component/Component.h"

class MeshGeometry;
class Shader;
class FrustumCulling;


class RenderComponent : public Component
{
public:
	RenderComponent();

	MeshGeometry* mGeo = nullptr;

	Shader* mShader = nullptr;

	FrustumCulling* mBbox = nullptr;
};

