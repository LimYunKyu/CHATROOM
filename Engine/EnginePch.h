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


#include "Define.h"
#include "Struct.h"

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

extern unique_ptr<class Engine> GEngine;