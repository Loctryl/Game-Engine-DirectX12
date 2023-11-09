#pragma once
#include "Shader.h"

// Simply renders a object with a given texture.
class TextureShader : public Shader
{
public:
	struct PassConstTexture : public ConstBuffer {
		XMFLOAT4X4 mViewProj;
	};

	struct ObjConstTexture : public ConstBuffer {
		XMFLOAT4X4 mWorld;
		XMFLOAT4 mColor;
	};

	TextureShader() = default;
	~TextureShader() override = default;

	bool OnCreate() override;
	UploadBufferBase* OnCreatePassUploadBuffer() override;
	UploadBufferBase* OnCreateObjectUploadBuffer() override;
	inline ConstBuffer* GetPassCB() override { return &mPc; }
	inline ConstBuffer* GetObjectCB() override { return &mOc; }
	void SetPassCB() override;
	void SetObjectCB(RenderComponent* renderItem) override;

	void Begin(ID3D12GraphicsCommandList* list) override;

	PassConstTexture mPc;
	ObjConstTexture mOc;
};