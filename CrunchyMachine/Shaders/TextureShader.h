#pragma once
#include "Shader.h"

// Simply renders a object with a given texture.
class TextureShader : public Shader
{
public:
	struct PassConstTexture : public ConstBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstTexture : public ConstBuffer {
		XMFLOAT4X4 world;
		XMFLOAT4 color;
	};

	TextureShader() = default;
	~TextureShader() = default;

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstBuffer* GetPassCB() { return &mPc; }
	virtual ConstBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB();
	virtual void SetObjectCB(XMFLOAT4X4 world, XMFLOAT4 color) { mOc.world = world; mOc.color = color; }

	virtual void TextureShader::Begin(ID3D12GraphicsCommandList* list);

	PassConstTexture mPc;
	ObjConstTexture mOc;
};