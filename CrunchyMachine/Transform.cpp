#include "Transform.h"

Transform::Transform()
{

}

void Transform::Translate(FXMVECTOR translation)
{
	//Load World Position Data
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
}

void Transform::SetPosition(FXMVECTOR position)
{
	//Store new position
	XMStoreFloat3(&worldPosition, position);
}

void Transform::SetPosition(XMFLOAT3 position)
{
	//Store new position
	worldPosition = position;
}

void Transform::SetPosition(FLOAT x, FLOAT y, FLOAT z)
{
	XMStoreFloat3(&worldPosition, XMVectorSet(x, y, z, 0.0f));
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
	//Make argument into usable vector & Recall Rotate
	Rotate(XMLoadFloat4(&rotationVector));
}

void Transform::Rotate(FLOAT x, FLOAT y, FLOAT z)
{
	//Load Rotation Data
	XMVECTOR tempRotation = XMLoadFloat4(&rotation);
	//Compute Rotation Quaternion & Apply it to object rotation
	tempRotation *= XMQuaternionRotationRollPitchYaw(x, y, z);
	//Store Rotation Data
	XMStoreFloat4(&rotation, tempRotation);
}
