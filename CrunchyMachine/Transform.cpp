#include "Transform.h"

XMFLOAT3 Transform::GetPosition()
{
	return worldPosition;
}

XMFLOAT3 Transform::GetLocalPosition()
{
	return localPosition;
}

XMFLOAT4 Transform::GetRotation()
{
	return rotation;
}

XMFLOAT3 Transform::GetScale()
{
	return scale;
}

void Transform::Translate(FXMVECTOR translation)
{
	//Load World Position Data & Rotation
	XMVECTOR tempPosition = XMLoadFloat3(&worldPosition);

	//Translate & Store Position Data
	XMStoreFloat3(&worldPosition, tempPosition + translation);
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
	//cout << "elements received : " << x << " , " << y << " , " << z;
}

void Transform::SetPosition(FXMVECTOR position)
{
	//Store new position
	XMStoreFloat3(&worldPosition, position);
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
	XMVECTOR tempPosition = XMLoadFloat3(&localPosition);

	//Translate & Store Position Data
	XMStoreFloat3(&localPosition, tempPosition + translation);
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
	XMStoreFloat3(&localPosition, position);
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

void Transform::Rotate(FXMVECTOR rotationVector)
{
	//Load Rotation Data
	XMVECTOR tempRotation = XMLoadFloat4(&rotation);
	//Compute Rotation Quaternion & Apply it to object rotation
	tempRotation *= XMQuaternionRotationRollPitchYawFromVector(rotationVector);
	//Store Rotation Data
	XMStoreFloat4(&rotation, tempRotation);
}

void Transform::Rotate(XMFLOAT4 rotationVector)
{
	//Load argument into usable vector & Recall Rotate
	Rotate(XMLoadFloat4(&rotationVector));
}

void Transform::Rotate(FLOAT x, FLOAT y, FLOAT z)
{
	//Make arguments intot usable vector & Recall Rotate
	Rotate(XMQuaternionRotationRollPitchYaw(x, y, z));
}

void Transform::SetScale(FXMVECTOR newScale)
{
	//Store new scale
	XMStoreFloat3(&scale, newScale);
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
