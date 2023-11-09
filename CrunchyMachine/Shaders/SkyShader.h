#pragma once
#include "Shader.h"

// Specific shader for skybox
class SkyShader : public Shader
{
public:
	struct PassConstSkyTex : public ConstBuffer {
		XMFLOAT4X4 mViewProj;
		XMFLOAT3 mEyePos;
	};

	struct ObjConstSkyTex : public ConstBuffer {
		XMFLOAT4X4 mWorld;
	};

	SkyShader() = default;
	~SkyShader() override = default;

	bool OnCreate() override;
	UploadBufferBase* OnCreatePassUploadBuffer() override;
	UploadBufferBase* OnCreateObjectUploadBuffer() override;
	inline ConstBuffer* GetPassCB() override { return &mPc; }
	inline ConstBuffer* GetObjectCB() override { return &mOc; }
	void SetPassCB() override;
	void SetObjectCB(RenderComponent* renderItem) override;

	void Begin(ID3D12GraphicsCommandList* list) override;

	PassConstSkyTex mPc;
	ObjConstSkyTex mOc;
};