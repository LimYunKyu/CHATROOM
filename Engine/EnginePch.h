#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
//#include <memory.h>
#include <tchar.h>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <string>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXMath.h>

#include "DirectXTex.h"
#include "DirectXTex.inl"

#include "Define.h"
#include "Struct.h"


#include "CorePch.h"

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace std;


#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")


#ifdef _DEBUG
#pragma comment(lib,"Engine\\Debug\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "Engine\\Release\\DirectXTex.lib")
#endif


#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib,"Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib,"Protobuf\\Release\\libprotobuf.lib")
#endif


extern unique_ptr<class Engine> GEngine;