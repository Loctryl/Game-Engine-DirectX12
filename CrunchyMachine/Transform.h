#include "Resources/framework.h"

class Transform
{

	XMFLOAT3 mPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 mLocalPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 mScale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMFLOAT3 mDirX = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 mDirY = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 mDirZ = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT4 mQuaternion = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4X4 mRotationMatrix;

	XMFLOAT4X4 mWorldMatrix;

public:

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLocalPosition();
	XMFLOAT4 GetRotation();
	XMFLOAT3 GetScale();
	XMFLOAT4X4 GetWorldMatrix();
	XMFLOAT4X4 GetWorldMatrixTranspose();

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

	void Rotate(XMFLOAT3 rotationVector);
	void Rotate(FLOAT x, FLOAT y, FLOAT z);

	void SetScale(FXMVECTOR newScale);
	void SetScale(XMFLOAT3 newScale);
	void SetScale(FLOAT x, FLOAT y, FLOAT z);

	void CalcWorldMatrix();
	//XMVECTOR LocalToWorld(FXMVECTOR localPosition);
};

