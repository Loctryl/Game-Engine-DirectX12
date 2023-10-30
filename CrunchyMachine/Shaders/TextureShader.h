#pragma once
#include "Shader.h"

class TextureShader : public Shader
{
public:
	struct PassConstBasic : public ConstantBuffer {
		XMFLOAT4X4 viewProj;
	};

	struct ObjConstantsBasic : public ConstantBuffer {
		XMFLOAT4X4 world;
	};

	TextureShader();
	virtual ~TextureShader();

	virtual bool OnCreate();
	virtual UploadBufferBase* OnCreatePassUploadBuffer();
	virtual UploadBufferBase* OnCreateObjectUploadBuffer();
	virtual ConstantBuffer* GetPassCB() { return &mPc; }
	virtual ConstantBuffer* GetObjectCB() { return &mOc; }
	virtual void SetPassCB(XMFLOAT4X4 viewProj) { mPc.viewProj = viewProj; }
	virtual void SetObjectCB(XMFLOAT4X4 world) { mOc.world = world; }
	virtual void SetTexture(Texture* texture) { mTexture = texture; }

	PassConstBasic mPc;
	ObjConstantsBasic mOc;

	Texture* mTexture;
};

