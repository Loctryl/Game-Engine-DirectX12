#pragma once
#include "Shaders/Shader.h"

// Simply renders a object with a given texture.
class DigitUIShader : public Shader
{
public:
	struct PassConstUI : public ConstBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstUI : public ConstBuffer {
		XMFLOAT4X4 world;
		XMFLOAT4 color;
		int digit;
	};

	DigitUIShader() = default;
	~DigitUIShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB();
	virtual void SetObjectCB(RenderComponent* renderItem);

	virtual void DigitUIShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstUI mPc;
	ObjConstUI mOc;
};