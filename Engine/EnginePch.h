#pragma once

#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
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

#include <wrl.h>
#include "DirectXTex.h"
#include "DirectXTex.inl"

#include <dwrite.h>
#include <d2d1.h>
#include <wchar.h>
#include <d2d1helper.h>
#include <wincodec.h>

#include "Define.h"
#include "Struct.h"

#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif


#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif


using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
using namespace std;






#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "d3dcompiler")
#ifdef _DEBUG
#pragma comment(lib,"DirectXTexd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

#pragma comment(lib, "d2d1")
#pragma comment(lib, "Dwrite.lib")

extern unique_ptr<class Engine> GEngine;