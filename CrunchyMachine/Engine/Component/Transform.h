#pragma once
#include "EngineResources/framework.h"
#include "Engine/Component/Component.h"

// This component stores and manages all the information about the game object in space.
// It stores the position, the rotation and the scale, as Unity's Transform.
// It provides getter and setter function for each element.
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
	~Transform() override;

	void CalcSuperWorldMatrix();

	inline XMFLOAT3 GetPosition() const { return mPosition; }
	XMFLOAT3 GetWorldPosition();
	
	inline XMFLOAT4 GetRotation() const { return mQuaternion; }
	inline XMFLOAT3 GetScale() const { return mScale; }
	
	inline XMFLOAT3 GetDirectionX() const { return mDirX; }
	inline XMFLOAT3 GetDirectionY() const { return mDirY; }
	inline XMFLOAT3 GetDirectionZ() const { return mDirZ; }
	
	inline XMFLOAT4X4 GetWorldMatrix() const { return mWorldMatrix; }
	XMFLOAT4X4 GetWorldMatrixTranspose() const;
	
	inline XMFLOAT4X4 GetSuperWorldMatrix() const { return mSuperWorldMatrix; }
	XMFLOAT4X4 GetSuperWorldMatrixTranspose() const;

	void XM_CALLCONV Translate(FXMVECTOR translation);
	void Translate(XMFLOAT3 translation);
	void Translate(FLOAT x, FLOAT y, FLOAT z);

	void XM_CALLCONV SetPosition(FXMVECTOR position);
	void SetPosition(XMFLOAT3 position);
	void SetPosition(FLOAT x, FLOAT y, FLOAT z);

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
};