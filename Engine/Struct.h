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