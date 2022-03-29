#include "pch.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Engine.h"

XMMATRIX Camera::mViewMatrix = XMMatrixIdentity();
XMMATRIX Camera::mProjectionMatrix = XMMatrixIdentity();


Camera::Camera() : Component(COMPONENT_TYPE::CAMARA)
{
	_width = WINFO.ClientWidth;
	_height = WINFO.ClientHeight;

}

void Camera::Update()
{
	



}

void Camera::LateUpdate()
{

	
	XMFLOAT3 pos = mGameObject.lock()->GetTransform()->GetPosition();
	if (pos.x + (_width / 2) >= (currentMapSize.MapSizeX / 2))
	{
		pos.x = (currentMapSize.MapSizeX / 2) - (_width / 2);
	}

	if (pos.x - (_width / 2) <= -(currentMapSize.MapSizeX / 2))
	{
		pos.x = -(currentMapSize.MapSizeX / 2) + (_width / 2);
	}

	if (pos.y + (_height / 2) >= (currentMapSize.MapSizeY / 2))
	{
		pos.y = (currentMapSize.MapSizeY / 2) - (_height / 2);
	}

	if (pos.y - (_height / 2) <= -(currentMapSize.MapSizeY / 2))
	{
		pos.y = -(currentMapSize.MapSizeY / 2) + (_height / 2);
	}


	XMMATRIX WorldMatrix = XMMatrixTranslation(pos.x, pos.y, -1.0f);

	mViewMatrix = XMMatrixInverse(nullptr, WorldMatrix);

	//mProjectionMatrix = ::XMMatrixPerspectiveFovLH(XMConvertToRadians(45.f), _width / _height, _near, _far);
	mProjectionMatrix = ::XMMatrixOrthographicLH(WINFO.ClientWidth , WINFO.ClientHeight, _near, _far);

}
