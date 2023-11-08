#pragma once
#include "Shader.h"

// Simply renders a object with a given texture.
class LitTextureShader : public Shader
{
public:
	struct PassConstLitTex : public ConstBuffer {
		XMFLOAT4X4 viewProj;
		XMFLOAT4 diffuseAlbedo;
		XMFLOAT4 lightColor;

		XMFLOAT3 eyePos;
		XMFLOAT3 lightDir;

		float roughness;
	};

	struct ObjConstLitTex : public ConstBuffer {
		XMFLOAT4X4 world;
		XMFLOAT4 color;
	};

	LitTextureShader() = default;
	~LitTextureShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB();
	virtual void SetObjectCB(RenderComponent* renderItem);

	virtual void LitTextureShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstLitTex mPc;
	ObjConstLitTex mOc;
};