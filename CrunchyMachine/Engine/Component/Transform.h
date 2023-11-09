#include "EngineResources/framework.h"
#include "Engine/Component/Component.h"

// This component stores and manages all the information about the game object in space.
// It stores the position, the rotation and the scale, as Unity's Transform.
// It provides getter and setter fonction for each element.
// Also calculate the world matrix for the render.
class Transform : public Component
{
private:
	XMFLOAT3 mPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 mLocalPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3 mScale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	XMFLOAT3 mDirX = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 mDirY = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3 mDirZ = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT4 mQuaternion = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4X4 mRotationMatrix;

	XMFLOAT4X4 mWorldMatrix;
	XMFLOAT4X4 mSuperWorldMatrix;

	bool mIsDirty = true;

public:
	Transform(GameObject* go);
	~Transform();

	void CalcSuperWorldMatrix();

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetWorldPosition();
	XMFLOAT3 GetLocalPosition();
	XMFLOAT4 GetRotation();
	XMFLOAT3 GetScale();
	XMFLOAT3 GetDirectionX();
	XMFLOAT3 GetDirectionY();
	XMFLOAT3 GetDirectionZ();
	XMFLOAT4X4 GetWorldMatrix();
	XMFLOAT3 GetDirz();
	XMFLOAT4X4 GetWorldMatrixTranspose();
	XMFLOAT4X4 GetSuperWorldMatrix();
	XMFLOAT4X4 GetSuperWorldMatrixTranspose();

	void XM_CALLCONV Translate(FXMVECTOR translation);
	void Translate(XMFLOAT3 translation);
	void Translate(FLOAT x, FLOAT y, FLOAT z);

	void XM_CALLCONV SetPosition(FXMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	void SetPosition(FLOAT x, FLOAT y, FLOAT z);

	void XM_CALLCONV TranslateLocal(FXMVECTOR translation);
	void TranslateLocal(XMFLOAT3 translation);
	void TranslateLocal(FLOAT x, FLOAT y, FLOAT z);

	void XM_CALLCONV SetPositionLocal(FXMVECTOR position);
	void SetPositionLocal(XMFLOAT3 position);
	void SetPositionLocal(FLOAT x, FLOAT y, FLOAT z);

	void SetRotation(XMFLOAT4 newRotation);
	void SetRotation(XMFLOAT3 newRotation);
	void SetDefaultRotation();

	void Roll(float angle);
	void Pitch(float angle);
	void Yaw(float angle);

	void RotateOnAxis(XMFLOAT3 rotationAxis, float angle);
	void RotateOnAxis(FLOAT x, FLOAT y, FLOAT z, float angle);

	void Rotate(XMFLOAT3 rotationVector);
	void Rotate(FLOAT x, FLOAT y, FLOAT z);

	void XM_CALLCONV SetScale(FXMVECTOR newScale);
	void SetScale(XMFLOAT3 newScale);
	void SetScale(FLOAT x, FLOAT y, FLOAT z);
	void SetScale(FLOAT scale);

	void CalcWorldMatrix();
	//XMVECTOR LocalToWorld(FXMVECTOR localPosition);
};