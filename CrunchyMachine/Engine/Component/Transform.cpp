#include "Transform.h"

Transform::Transform() { mComponentType = TRANSFORM; }

XMFLOAT3 Transform::GetPosition() { return mPosition; }

XMFLOAT3 Transform::GetLocalPosition() { return mLocalPosition; }

XMFLOAT4 Transform::GetRotation() { return mQuaternion; }

XMFLOAT3 Transform::GetScale() { return mScale; }

XMFLOAT4X4 Transform::GetWorldMatrix() { return mWorldMatrix; }

XMFLOAT3 Transform::GetDirz() { return mDirZ; }

XMFLOAT4X4 Transform::GetWorldMatrixTranspose()
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixTranspose(XMLoadFloat4x4(&mWorldMatrix)));
	return temp;
}

void Transform::Translate(FXMVECTOR translation)
{
	//Load World Position Data & Rotation
	XMVECTOR tempPosition = XMLoadFloat3(&mPosition);

	//Translate & Store Position Data
	XMStoreFloat3(&mPosition, tempPosition + translation);
}

void Transform::Translate(XMFLOAT3 translation)
{
	//Load argument into usable vector & Recall Translate
	Translate(XMLoadFloat3(&translation));
}

void Transform::Translate(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall Translate
	Translate(XMVectorSet(x, y, z, 0.0f));
}

void Transform::SetPosition(FXMVECTOR position)
{
	//Store new position
	XMStoreFloat3(&mPosition, position);
}

void Transform::SetPosition(XMFLOAT3 position)
{
	//Make argument into usable vector & Recall SetPosition
	SetPosition(XMLoadFloat3(&position));
}

void Transform::SetPosition(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall SetPosition
	SetPosition(XMVectorSet(x, y, z, 0.0f));
}

void Transform::TranslateLocal(FXMVECTOR translation)
{
	//Load Local Position Data
	XMVECTOR tempPosition = XMLoadFloat3(&mLocalPosition);
	XMVECTOR tempQuaternion = XMLoadFloat4(&mQuaternion);

	//Apply object rotation to translation vector
	XMVECTOR tempTranslation = XMQuaternionMultiply(translation, tempQuaternion);

	//Translate & Store Position Data
	XMStoreFloat3(&mLocalPosition, tempPosition + tempTranslation);
}

void Transform::TranslateLocal(XMFLOAT3 translation)
{
	//Load argument into usable vector & Recall Translate
	TranslateLocal(XMLoadFloat3(&translation));
}

void Transform::TranslateLocal(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall Translate
	TranslateLocal(XMVectorSet(x, y, z, 0.0f));
}

void Transform::SetPositionLocal(FXMVECTOR position)
{
	//Store new position
	XMStoreFloat3(&mLocalPosition, position);
}

void Transform::SetPositionLocal(XMFLOAT3 position)
{
	//Make argument into usable vector & Recall SetPosition
	SetPositionLocal(XMLoadFloat3(&position));
}

void Transform::SetPositionLocal(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall SetPosition
	SetPositionLocal(XMVectorSet(x, y, z, 0.0f));
}

void Transform::Rotate(XMFLOAT3 rotationVector)
{
	//Load Rotation Datas
	XMVECTOR tempDirX = XMLoadFloat3(&mDirX);
	XMVECTOR tempDirY = XMLoadFloat3(&mDirY);
	XMVECTOR tempDirZ = XMLoadFloat3(&mDirZ);
	XMVECTOR tempQuaternion = XMLoadFloat4(&mQuaternion);

	//Apply each angle to vanilla calcQuaternion
	XMVECTOR calcQuaternion = XMQuaternionIdentity();

	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirX, rotationVector.x));
	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirY, rotationVector.y));
	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirZ, rotationVector.z));

	//Add Rotation to current rotation quaternion & Store modification
	tempQuaternion = XMQuaternionMultiply(tempQuaternion, calcQuaternion);
	XMStoreFloat4(&mQuaternion, tempQuaternion);

	//Convert current rotation quaternion to rotation matrix
	XMStoreFloat4x4(&mRotationMatrix, XMMatrixRotationQuaternion(tempQuaternion));

	//Update all axis values
	mDirX.x = mRotationMatrix._11;
	mDirX.y = mRotationMatrix._12;
	mDirX.z = mRotationMatrix._13;

	mDirY.x = mRotationMatrix._21;
	mDirY.y = mRotationMatrix._22;
	mDirY.z = mRotationMatrix._23;

	mDirZ.x = mRotationMatrix._31;
	mDirZ.y = mRotationMatrix._32;
	mDirZ.z = mRotationMatrix._33;
}

void Transform::Rotate(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments intot usable vector & Recall Rotate
	Rotate(XMFLOAT3(x, y, z));
}

void Transform::SetScale(FXMVECTOR newScale)
{
	//Store new scale
	XMStoreFloat3(&mScale, newScale);
}

void Transform::SetScale(XMFLOAT3 newScale)
{
	//Load argument into usable vector & Recall SetScale
	SetScale(XMLoadFloat3(&newScale));
}

void Transform::SetScale(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall SetScale
	SetScale(XMVectorSet(x, y, z, 0.0f));
}

void Transform::CalcWorldMatrix()
{
	//Scale * rotation * pos
	XMMATRIX tempMatrix = XMMatrixIdentity();

	tempMatrix = tempMatrix
		* XMMatrixScaling(mScale.x, mScale.y, mScale.z)
		* XMMatrixRotationQuaternion(XMLoadFloat4(&mQuaternion))
		* XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);

	XMStoreFloat4x4(&mWorldMatrix, tempMatrix);
}
