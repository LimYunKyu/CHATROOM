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

struct TransformParams
{
	XMMATRIX matWorld;
	XMMATRIX matView;
	XMMATRIX matProjection;
	XMMATRIX matWV;
	XMMATRIX matWVP;
};

struct TEXTURE_ON {
	int Tex0_On;
	int Tex1_On;
	int Tex2_On;
	int Tex3_On;
	int Tex4_On;


};

enum class CBV_REGISTER : UINT8
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};

enum class SRV_REGISTER : UINT8
{
	t0 = static_cast<UINT8>(CBV_REGISTER::END),
	t1,
	t2,
	t3,
	t4,

	END
};

struct FontType
{
	float left, right;
	int size;

};

struct SentenceType
{
	ID3D11Buffer* vertexBuffer, * indexBuffer;
	int vertexCount, indexCount, maxLength;
	float red, green, blue;
};
