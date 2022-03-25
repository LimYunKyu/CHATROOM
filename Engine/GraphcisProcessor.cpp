#include "pch.h"
#include "GraphcisProcessor.h"
#include "Engine.h"


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
	CreateDevice();
	CreateSwapChain();
	CreateDepthStencilView();
	SetUpViewPort();
	CreateSampleState();



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
	

	//mDeviceContext->PSSetSamplers(0, 1, &mSamplerState);
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Brown));
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

void GraphcisProcessor::RenderEnd()
{
	mSwapChain->Present(0, 0);
}



bool GraphcisProcessor::CreateDevice()
{
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
		0,                 // default adapter
		md3dDriverType,
		0,                 // no software device
		createDeviceFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),              // default feature level array
		D3D11_SDK_VERSION,
		&mDevice,
		&featureLevel,
		&mDeviceContext);


	if (FAILED(hr))
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;

	}
	return true;
}

bool GraphcisProcessor::CreateSwapChain()
{
	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	assert(m4xMsaaQuality > 0);



	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = WINFO.ClientWidth;
	sd.BufferDesc.Height = WINFO.ClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	if (mEnable4xMsaa)
	{
		sd.SampleDesc.Count = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
	}

	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = WINFO.hWnd;
	sd.Windowed = WINFO.windowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	if (FAILED(mDevice->QueryInterface(IID_PPV_ARGS(&mdxgiDevice))))
	{
		MessageBox(0, L"QueryInterface Failed.", 0, 0);

		return false;
	}

	if (FAILED(mdxgiDevice->GetParent(IID_PPV_ARGS(&mdxgiAdapter))))
	{
		MessageBox(0, L"Get mdxgiAdapter Failed.", 0, 0);

		return false;
	}
	if (FAILED(mdxgiAdapter->GetParent(IID_PPV_ARGS(&mdxgiFactory))))
	{
		MessageBox(0, L"Get mdxgiFactory Failed.", 0, 0);
		return false;
	}
	if (FAILED(mdxgiFactory->CreateSwapChain(mDevice, &sd, &mSwapChain)))
	{
		MessageBox(0, L"CreateSwapChain Failed.", 0, 0);
		return false;
	}

	if (FAILED(mSwapChain->GetBuffer(0, IID_PPV_ARGS(&mBackBuffer))))
	{
		MessageBox(0, L"Get BackBuffer Failed.", 0, 0);
		return false;
	}

	if (FAILED(mDevice->CreateRenderTargetView(mBackBuffer, nullptr, &mRenderTargetView)))
	{
		MessageBox(0, L"Create RenderTargetView Failed.", 0, 0);
		return false;
	}


	ReleaseCOM(mdxgiDevice);
	ReleaseCOM(mdxgiAdapter);
	ReleaseCOM(mdxgiFactory);

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
