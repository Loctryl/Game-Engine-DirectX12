#pragma once
#include "Shaders/Shader.h"

// Shader for static element on UI
class StaticUIShader : public Shader
{
public:
	struct PassConstUI : public ConstBuffer {
		XMFLOAT4X4 mViewProj;
	};

	struct ObjConstUI : public ConstBuffer {
		XMFLOAT4X4 mWorld;
		XMFLOAT4 mColor;
	};

	StaticUIShader() = default;
	~StaticUIShader() override = default;

	bool OnCreate() override;
	UploadBufferBase* OnCreatePassUploadBuffer() override;
	UploadBufferBase* OnCreateObjectUploadBuffer() override;
	inline ConstBuffer* GetPassCB() override { return &mPc; }
	inline ConstBuffer* GetObjectCB() override { return &mOc; }
	void SetPassCB() override;
	void SetObjectCB(RenderComponent* renderItem) override;

	void Begin(ID3D12GraphicsCommandList* list) override;

	PassConstUI mPc;
	ObjConstUI mOc;
};

