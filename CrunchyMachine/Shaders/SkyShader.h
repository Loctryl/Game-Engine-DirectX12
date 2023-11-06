#pragma once
#include "Shader.h"

// 
class SkyShader : public Shader
{
public:
	struct PassConstSkyTex : public ConstBuffer {
		XMFLOAT4X4 viewProj;
		XMFLOAT3 eyePos;
	};

	struct ObjConstSkyTex : public ConstBuffer {
		XMFLOAT4X4 world;
	};

	SkyShader() = default;
	~SkyShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB();
	virtual void SetObjectCB(XMFLOAT4X4 world) { mOc.world = world; }

	virtual void SkyShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstSkyTex mPc;
	ObjConstSkyTex mOc;
};