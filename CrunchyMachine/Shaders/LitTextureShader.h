#pragma once
#include "Shader.h"

// Simply renders a object with a given texture.
class LitTextureShader : public Shader
{
public:
	struct PassConstLitTex : public ConstBuffer {
		XMFLOAT4X4 mViewProj;
		XMFLOAT4 mDiffuseAlbedo;
		XMFLOAT4 mLightColor;

		XMFLOAT3 mEyePos;
		XMFLOAT3 mLightDir;

		float mRoughness;
	};

	struct ObjConstLitTex : public ConstBuffer {
		XMFLOAT4X4 mWorld;
		XMFLOAT4 mColor;
	};

	LitTextureShader() = default;
	~LitTextureShader() override = default;

	bool OnCreate() override;
	UploadBufferBase* OnCreatePassUploadBuffer() override;
	UploadBufferBase* OnCreateObjectUploadBuffer() override;
	inline ConstBuffer* GetPassCB() override { return &mPc; }
	inline ConstBuffer* GetObjectCB() override { return &mOc; }
	void SetPassCB() override;
	void SetObjectCB(RenderComponent* renderItem) override;

	void Begin(ID3D12GraphicsCommandList* list) override;

	PassConstLitTex mPc;
	ObjConstLitTex mOc;
};