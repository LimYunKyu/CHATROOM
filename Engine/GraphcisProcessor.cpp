#include "pch.h"
#include "GraphcisProcessor.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Animator.h"
#include "ResourceManager.h"
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
	float ClearColor[4] = { 0.2f, 0.4f, 0.8f, 1.0f }; // red,green,blue,alpha
	mDeviceContext->PSSetSamplers(0, 1, &mSamplerState);
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, nullptr);
	//mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 1);
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, ClearColor);
	

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
	mViewPort.TopLeftX = 0.f;
	mViewPort.TopLeftY = 0.f;
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

ID3D11DeviceContext* GraphcisProcessor::GetDeviceContext()
{
	 return mDeviceContext; 
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

	//2d를 위해서는 z버퍼를 꺼줘야한다.
	D3D11_DEPTH_STENCIL_DESC DSState;
	DSState.DepthEnable = TRUE;
	DSState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DSState.DepthFunc = D3D11_COMPARISON_ALWAYS;

	mDevice->CreateDepthStencilState(&DSState, &mDepthStencilState);
	
	mDevice->CreateTexture2D(&descDepth, NULL, &mDepthStencilBuffer);

	mDevice->CreateDepthStencilView(mDepthStencilBuffer,nullptr, &mDepthStencilView);

}
