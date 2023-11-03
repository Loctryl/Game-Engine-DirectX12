#pragma once
#include "Shader.h"

// Simply renders a object with a given texture.
class LitShader : public Shader
{
public:
	struct PassConstLit : public ConstBuffer {
		XMFLOAT4X4 viewProj;
		XMFLOAT3 eyePos;

		XMFLOAT4 diffuseAlbedo;
		float roughness;

		XMFLOAT4 lightColor;
		XMFLOAT3 lightDir;
	};

	struct ObjConstLit : public ConstBuffer {
		XMFLOAT4X4 world;
	};

	LitShader() = default;
	~LitShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB(XMFLOAT4X4 viewProj);
	virtual void SetObjectCB(XMFLOAT4X4 world) { mOc.world = world; }

	virtual void LitShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstLit mPc;
	ObjConstLit mOc;
};