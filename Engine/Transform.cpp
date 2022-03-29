#include "pch.h"
#include "Transform.h"
#include "Camera.h"
#include "BufferManager.h"
#include "GameObject.h"

Transform::Transform(): Component(COMPONENT_TYPE::TRANSFORM)
{
	
	mTransMatrix = XMMatrixIdentity();
	mScaleMatrix = XMMatrixIdentity();
	mRotationMatrix = XMMatrixIdentity();
	mWorldMatrix = XMMatrixIdentity();

	mPos = {0.f,0.f,0.f};
	mScale = {1.f,1.f,1.f};
	mRotation = {0.f,0.f,0.f};

}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
	
	

	mScaleMatrix = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
	mRotationMatrix = XMMatrixRotationX(mRotation.x) * XMMatrixRotationY(mRotation.y) * XMMatrixRotationZ(mRotation.z);
	mTransMatrix = XMMatrixTranslation(mPos.x, mPos.y, mPos.z);


	mWorldMatrix = mScaleMatrix * mRotationMatrix * mTransMatrix;
}

void Transform::Render()
{
	PushData();
}

void Transform::SetPosition(XMFLOAT3 _pos)
{

	mPos = _pos;
	mTransMatrix = XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
	
}

void Transform::SetScale(XMFLOAT3 _scale)
{
	mScale = _scale;
	mScaleMatrix = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
}

void Transform::SeRotation(XMFLOAT3 _rotation)
{
	mRotation = _rotation;
	mScaleMatrix = XMMatrixRotationX(mRotation.x) * XMMatrixRotationY(mRotation.y) * XMMatrixRotationZ(mRotation.z);
}

void Transform::SetAddPosition(XMFLOAT3 _pos)
{
	mPos.x += _pos.x;
	mPos.y += _pos.y;
	mPos.z += _pos.z;
	mTransMatrix = XMMatrixTranslation(mPos.x, mPos.y, mPos.z);
}

void Transform::SetAddScale(XMFLOAT3 _scale)
{
	mPos.x += _scale.x;
	mPos.y += _scale.y; 
	mPos.z += _scale.z;
	mScaleMatrix = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
}

void Transform::SetAddRotation(XMFLOAT3 _rotation)
{
	mPos.x += _rotation.x; 
	mPos.y += _rotation.y;
	mPos.z += _rotation.z;
	mScaleMatrix = XMMatrixRotationX(mRotation.x) * XMMatrixRotationY(mRotation.y) * XMMatrixRotationZ(mRotation.z);
}

void Transform::PushData()
{
	TransformParams params;
	params.matWorld = mWorldMatrix;
	params.matView = Camera::GetViewMatrix();
	params.matProjection = Camera::GetProjectionMatrix();
	params.matWV = params.matWorld * params.matView;
	params.matWVP = params.matWorld * params.matView * params.matProjection;
	BufferManager::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&params);
}

