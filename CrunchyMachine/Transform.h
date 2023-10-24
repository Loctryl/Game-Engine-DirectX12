#include "Resources/framework.h"

class Transform
{

	XMFLOAT3 worldPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 localPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT4 rotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT3 scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

public:

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLocalPosition();
	XMFLOAT4 GetRotation();
	XMFLOAT3 GetScale();

	void Translate(FXMVECTOR translation);
	void Translate(XMFLOAT3 translation);
	void Translate(FLOAT x, FLOAT y, FLOAT z);

	void SetPosition(FXMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	void SetPosition(FLOAT x, FLOAT y, FLOAT z);

	void TranslateLocal(FXMVECTOR translation);
	void TranslateLocal(XMFLOAT3 translation);
	void TranslateLocal(FLOAT x, FLOAT y, FLOAT z);

	void SetPositionLocal(FXMVECTOR position);
	void SetPositionLocal(XMFLOAT3 position);
	void SetPositionLocal(FLOAT x, FLOAT y, FLOAT z);

	void Rotate(FXMVECTOR rotationVector);
	void Rotate(XMFLOAT4 rotationVector);
	void Rotate(FLOAT x, FLOAT y, FLOAT z);

	void SetScale(FXMVECTOR newScale);
	void SetScale(XMFLOAT3 newScale);
	void SetScale(FLOAT x, FLOAT y, FLOAT z);

	//XMVECTOR WorldToLocal(FXMVECTOR worldPosition);
	//XMVECTOR LocalToWorld(FXMVECTOR localPosition);
	// GetParent()
};

