#include "pch.h"
#include "GraphcisProcessor.h"
#include "Engine.h"

struct SimpleVertex
{
	XMFLOAT3 Pos;
};



GraphcisProcessor::GraphcisProcessor()
{
}

GraphcisProcessor::~GraphcisProcessor()
{
	ReleaseCOM(mDevice);
	ReleaseCOM(mDeviceContext);
	ReleaseCOM(mSwapChain);
	ReleaseCOM(mDepthStencilBuffer);
	ReleaseCOM(mBackBuffer);
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSamplerState);
}

bool GraphcisProcessor::Initialize()
{

	
	CreateDeviceAndSwapChain();
	SetUpViewPort();
	CreateShaderFile(L"..\\Shader\\Tutorial.fx");
	CreateVertexBuffer();
	CreateDepthStencilView();


	return true;
}

bool GraphcisProcessor::Update()
{
	

	return true;
}

bool GraphcisProcessor::Render()
{
	RenderBegin();

	RenderEnd();

	return true;
}

void GraphcisProcessor::RenderBegin()
{
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	 // Clear the back buffer 
	float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, ClearColor);
	
	// Render a triangle
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	mDeviceContext->DrawIndexed(mIndexCount,0, 0);

	
}

void GraphcisProcessor::RenderEnd()
{
	// Present the information rendered to the back buffer to the front buffer (the screen)
	mSwapChain->Present(0, 0);
}



bool GraphcisProcessor::CreateDeviceAndSwapChain()
{
	HRESULT hr = S_OK;

	

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINFO.ClientWidth;
	sd.BufferDesc.Height = WINFO.ClientHeight;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = WINFO.hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = WINFO.windowed;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		mdriverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, mdriverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &mSwapChain, &mDevice, &mfeatureLevel, &mDeviceContext);
		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return hr;

	// Create a render target view
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&mBackBuffer);
	if (FAILED(hr))
		return false;

	hr = mDevice->CreateRenderTargetView(mBackBuffer, NULL, &mRenderTargetView);
	
	if (FAILED(hr))
		return false;

	





	return true;
}

void GraphcisProcessor::SetUpViewPort()
{
	mViewPort.TopLeftX = 0;
	mViewPort.TopLeftY = 0;
	mViewPort.Width = static_cast<float>(WINFO.ClientWidth);
	mViewPort.Height = static_cast<float>(WINFO.ClientHeight);
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;

	mDeviceContext->RSSetViewports(1, &mViewPort);

	

}

void GraphcisProcessor::CreateSampleState()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if (FAILED(mDevice->CreateSamplerState(&sampDesc, &mSamplerState)))
	{
	
		MessageBox(0, L"CreateSamplerState Failed.", 0, 0);
	}


}



void GraphcisProcessor::CreateShaderFile(const wstring& path)
{
	HRESULT HR;

	UINT32 compileFlag = 0;
#ifdef _DEBUG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif


	ID3DBlob* VSblob;
	ID3DBlob* ERRblob;

	const D3D_SHADER_MACRO defines[] =
	{
		"EXAMPLE_DEFINE", "1",
		NULL, NULL
	};

	if (FAILED(HR = ::D3DCompileFromFile(path.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Main", "vs_5_0", compileFlag, 0, &VSblob, &ERRblob)))
	{
		::MessageBoxA(nullptr, "Vertex Shader Create Failed !", nullptr, MB_OK);
	}

	if (ERRblob)
	{
		OutputDebugStringA(reinterpret_cast<const char*>(ERRblob->GetBufferPointer()));
		MessageBox(GEngine->GetWinfo().hWnd, L"error compiling shader", path.c_str(), MB_OK);
	}

	HR = mDevice->CreateVertexShader(VSblob->GetBufferPointer(), VSblob->GetBufferSize(), NULL, &mVertexShader);

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the input layout
	mDevice->CreateInputLayout(layout, numElements, VSblob->GetBufferPointer(),
		VSblob->GetBufferSize(), &mVertexLayout);

	//VSblob->Release();

	mDeviceContext->IASetInputLayout(mVertexLayout);
	
	ID3DBlob* PSblob;

	if (FAILED(HR = ::D3DCompileFromFile(path.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Main", "ps_5_0", compileFlag, 0, &PSblob, &ERRblob)))
	{
		::MessageBoxA(nullptr, "Vertex Shader Create Failed !", nullptr, MB_OK);
	}


	mDevice->CreatePixelShader(PSblob->GetBufferPointer(), PSblob->GetBufferSize(), NULL, &mPixelShader);
	PSblob->Release();
	


}

void GraphcisProcessor::CreateVertexBuffer()
{
	float w2 = 0.5f;
	float h2 = 0.5f;


	// Create vertex buffer
	
	vector<Vertex> vertices =
	{
		{XMFLOAT3(-w2, -h2, 0.5f),XMFLOAT2(0.f,0.f)},
		{XMFLOAT3(-w2, +h2, 0.5f),XMFLOAT2(1.f,0.f)},
		{XMFLOAT3(+w2, +h2, 0.5f),XMFLOAT2(1.f,1.f)},
		{XMFLOAT3(+w2, -h2, 0.5f),XMFLOAT2(0.f,1.f)},

	};






	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) *vertices.size() ;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &(vertices[0]);
	mDevice->CreateBuffer(&bd, &InitData, &mVertexBuffer);
	

	// Set vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);


	vector<UINT32> idx(6);

	// ¾Õ¸é
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;


	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * idx.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &(idx[0]);

	mDevice->CreateBuffer(&ibd, &iinitData, &mIndexBuffer);

	mIndexCount = idx.size();
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);







	// Set primitive topology
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);




}

bool GraphcisProcessor::ScreenResize()
{
	return true;
}

void GraphcisProcessor::CreateDepthStencilView()
{
	ID3D11Texture2D* pDepthStencil = NULL;
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINFO.ClientWidth;
	descDepth.Height = WINFO.ClientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	
	mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencilBuffer);
	mDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView);

}
