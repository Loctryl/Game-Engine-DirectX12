#include "Resources/framework.h"

class Transform
{

private:

	XMFLOAT3 worldPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 localPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4 rotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);


	void Translate(FXMVECTOR translation);
	void Translate(XMFLOAT3 translation);
	void Translate(FLOAT x, FLOAT y, FLOAT z);

	void SetPosition(FXMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	void SetPosition(FLOAT x, FLOAT y, FLOAT z);

	void TranslateLocal(FXMVECTOR translation);
	void TranslateLocal(XMFLOAT3 translation);
	void TranslateLocal(FLOAT x, FLOAT y, FLOAT z);

	void Rotate(FXMVECTOR rotationVector);
	void Rotate(XMFLOAT4 rotationVector);
	void Rotate(FLOAT x, FLOAT y, FLOAT z);

public:

	XMVECTOR WorldToLocal(FXMVECTOR worldPosition);
	XMVECTOR LocalToWorld(FXMVECTOR localPosition);
	// GetParent()
};

