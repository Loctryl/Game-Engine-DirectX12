#include "Transform.h"
#include "Engine/GameObject.h"

Transform::Transform(GameObject* go) 
{ 
	mGameObject = go;
	mComponentType = TRANSFORM;
	XMStoreFloat4x4(&mRotationMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&mWorldMatrix, XMMatrixIdentity());
	XMStoreFloat4x4(&mSuperWorldMatrix, XMMatrixIdentity());
}

Transform::~Transform() { }

void Transform::CalcSuperWorldMatrix()
{
	XMFLOAT4X4 parentSuperWordMatix;

	GameObject* parent = mGameObject->GetParent();

	if (parent) {
		parent->mTransform->CalcSuperWorldMatrix();
		parentSuperWordMatix = parent->mTransform->GetSuperWorldMatrix();
	}
	else {
		XMStoreFloat4x4(&parentSuperWordMatix,XMMatrixIdentity());
	}

	CalcWorldMatrix();
	XMStoreFloat4x4(&mSuperWorldMatrix,XMMatrixMultiply(XMLoadFloat4x4(&mWorldMatrix),XMLoadFloat4x4(&parentSuperWordMatix)));
}

XMFLOAT3 Transform::GetWorldPosition() {
	CalcSuperWorldMatrix();
	return XMFLOAT3(mSuperWorldMatrix._41, mSuperWorldMatrix._42, mSuperWorldMatrix._43);
}

XMFLOAT4X4 Transform::GetWorldMatrixTranspose() const
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixTranspose(XMLoadFloat4x4(&mWorldMatrix)));
	return temp;
}

XMFLOAT4X4 Transform::GetSuperWorldMatrixTranspose() const
{
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, XMMatrixTranspose(XMLoadFloat4x4(&mSuperWorldMatrix)));
	return temp;
}

void XM_CALLCONV Transform::Translate(FXMVECTOR translation)
{
	//Load World Position Data & Rotation
	XMVECTOR tempPosition = XMLoadFloat3(&mPosition);

	//Translate & Store Position Data
	XMStoreFloat3(&mPosition, tempPosition + translation);
	mIsDirty = true;
}

void Transform::Translate(XMFLOAT3 translation)
{
	//Load argument into usable vector & Recall Translate
	Translate(XMLoadFloat3(&translation));
	mIsDirty = true;
}

void Transform::Translate(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall Translate
	Translate(XMVectorSet(x, y, z, 0.0f));
	mIsDirty = true;
}


void XM_CALLCONV Transform::SetPosition(FXMVECTOR position)
{
	//Store new position
	XMStoreFloat3(&mPosition, position);
	mIsDirty = true;
}

void Transform::SetPosition(XMFLOAT3 position)
{
	mPosition = position;
	mIsDirty = true;
}

void Transform::SetPosition(FLOAT x, FLOAT y, FLOAT z)
{
	mPosition = XMFLOAT3(x,y,z);
	mIsDirty = true;
}


void Transform::SetRotation(XMFLOAT4 newRotation) {
	mQuaternion = newRotation;
	XMVECTOR tempQuaternion = XMLoadFloat4(&mQuaternion);

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

	mIsDirty = true;
}

void Transform::SetRotation(XMFLOAT3 newRotation)
{
	SetDefaultRotation();
	Rotate(newRotation);
}

void Transform::SetDefaultRotation()
{
	XMStoreFloat4x4(&mRotationMatrix, XMMatrixRotationQuaternion(XMQuaternionIdentity()));

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

	mIsDirty = true;
}


void Transform::Roll(float angle) 
{
	XMFLOAT3 front = GetDirectionZ();
	RotateOnAxis(front, angle);
}

void Transform::Pitch(float angle)
{
	XMFLOAT3 front = GetDirectionX();
	RotateOnAxis(front, angle);
}

void Transform::Yaw(float angle)
{
	XMFLOAT3 front = GetDirectionY();
	RotateOnAxis(front, angle);
}

void Transform::RotateOnAxis(XMFLOAT3 rotationAxis, float angle) {

	XMVECTOR axis = XMLoadFloat3(&rotationAxis);
	XMVECTOR tempQuaternion = XMLoadFloat4(&mQuaternion);
	XMVECTOR calcQuaternion = XMQuaternionIdentity();

	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(axis, XMConvertToRadians(angle)));

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

	mIsDirty = true;
}

void Transform::RotateOnAxis(FLOAT x, FLOAT y, FLOAT z, float angle) { RotateOnAxis(XMFLOAT3(x, y, z), angle); }

void Transform::Rotate(XMFLOAT3 rotationVector)
{
	//Load Rotation Datas
	XMVECTOR tempDirX = XMLoadFloat3(&mDirX);
	XMVECTOR tempDirY = XMLoadFloat3(&mDirY);
	XMVECTOR tempDirZ = XMLoadFloat3(&mDirZ);
	XMVECTOR tempQuaternion = XMLoadFloat4(&mQuaternion);

	//Apply each angle to vanilla calcQuaternion
	XMVECTOR calcQuaternion = XMQuaternionIdentity();

	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirX, XMConvertToRadians(rotationVector.x)));
	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirY, XMConvertToRadians(rotationVector.y)));
	calcQuaternion = XMQuaternionMultiply(calcQuaternion, XMQuaternionRotationAxis(tempDirZ, XMConvertToRadians(rotationVector.z)));

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

	mIsDirty = true;
}

void Transform::Rotate(FLOAT x, FLOAT y, FLOAT z) { Rotate(XMFLOAT3(x, y, z)); }

void XM_CALLCONV Transform::SetScale(FXMVECTOR newScale)
{
	//Store new scale
	XMStoreFloat3(&mScale, newScale);
	mIsDirty = true;
}

void Transform::SetScale(XMFLOAT3 newScale)
{
	//Load argument into usable vector & Recall SetScale
	SetScale(XMLoadFloat3(&newScale));
	mIsDirty = true;
}

void Transform::SetScale(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments into usable vector & Recall SetScale
	SetScale(XMVectorSet(x, y, z, 0.0f));
	mIsDirty = true;
}

void Transform::SetScale(FLOAT scale) {
	SetScale(scale, scale, scale);
	mIsDirty = true;
}


void Transform::CalcWorldMatrix()
{
	if (!mIsDirty) return;

	//Scale * rotation * pos
	XMMATRIX tempMatrix = XMMatrixIdentity();

	tempMatrix = tempMatrix
		* XMMatrixScaling(mScale.x, mScale.y, mScale.z)
		* XMMatrixRotationQuaternion(XMLoadFloat4(&mQuaternion))
		* XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);

	XMStoreFloat4x4(&mWorldMatrix, tempMatrix);

	mIsDirty = false;
}
