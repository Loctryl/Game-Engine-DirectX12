#pragma once
#include "Shaders/Shader.h"

class StaticUIShader : public Shader
{
public:
	struct PassConstUI : public ConstBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstUI : public ConstBuffer {
		XMFLOAT4X4 world;
		XMFLOAT4 color;
	};

	StaticUIShader() = default;
	~StaticUIShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB();
	virtual void SetObjectCB(RenderComponent* renderItem);

	virtual void StaticUIShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstUI mPc;
	ObjConstUI mOc;
};

