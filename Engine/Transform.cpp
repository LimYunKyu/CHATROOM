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
	mParentPos = { 0.f,0.f,0.f };
	mWorldPos = { 0.f,0.f,0.f };
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{


	if (mGameObject.lock()->GetParentObject().get())
	{
		mParentPos = mGameObject.lock()->GetParentObject()->GetTransform()->GetWorldPosition();
		
	}
	else
	{
		if (mWorldPos.z != 0 && (mGameObject.lock()->GetOBJName() == L"Player"))
			int a = 5;
	}
	mWorldPos = mPos;
	mWorldPos = { mPos.x + mParentPos.x,mPos.y + mParentPos.y,mPos.z + mParentPos.z };

	mScaleMatrix = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
	mRotationMatrix = XMMatrixRotationX(mRotation.x) * XMMatrixRotationY(mRotation.y) * XMMatrixRotationZ(mRotation.z);
	mTransMatrix = XMMatrixTranslation(mWorldPos.x, mWorldPos.y, mWorldPos.z);

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
	mScale.x += _scale.x;
	mScale.y += _scale.y;
	mScale.z += _scale.z;
	mScaleMatrix = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
}

void Transform::SetAddRotation(XMFLOAT3 _rotation)
{
	mRotation.x += _rotation.x; 
	mRotation.y += _rotation.y;
	mRotation.z += _rotation.z;
	mScaleMatrix = XMMatrixRotationX(mRotation.x) * XMMatrixRotationY(mRotation.y) * XMMatrixRotationZ(mRotation.z);
}

void Transform::SetParentPos(XMFLOAT3 _parentpos)
{
	mParentPos.x = _parentpos.x;
	mParentPos.y = _parentpos.y;
	mParentPos.z = _parentpos.z;

}

void Transform::SetWorldPos(XMFLOAT3 _worldpos)
{
	mWorldPos.x = _worldpos.x;
	mWorldPos.y = _worldpos.y;
	mWorldPos.z = _worldpos.z;

	XMMATRIX mTempPosMatrix = XMMatrixTranslation(mWorldPos.x, mWorldPos.y, mWorldPos.z);
	
	mWorldMatrix = mScaleMatrix * mRotationMatrix * mTempPosMatrix;




}

void Transform::PushData()
{

	


	TransformParams params;
	params.matWorld = mWorldMatrix;
	params.matView = Camera::GetViewMatrix();
	params.matProjection = Camera::GetProjectionMatrix();
	params.matWV = params.matWorld * params.matView;
	params.matWVP = params.matWorld * params.matView * params.matProjection;


	if (mMoveType == MOVETYPE::FIX)
	{
		params.matWorld = mWorldMatrix;
		params.matView = XMMatrixIdentity();
		params.matProjection = Camera::GetProjectionMatrix();
		params.matWV = params.matWorld * params.matView;
		params.matWVP = params.matWorld * params.matView * params.matProjection;
	}
		

	BufferManager::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&params);
}

