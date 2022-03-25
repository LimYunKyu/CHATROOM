#pragma once

#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;
struct WindowInfo
{

	float ClientWidth;
	float ClientHeight;
	HWND hWnd;
	bool  windowed;

};


struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};