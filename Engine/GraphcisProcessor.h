#pragma once
class GraphcisProcessor
{

public:
	GraphcisProcessor();
	~GraphcisProcessor();
public:
	bool Initialize();
	bool Update();
	bool Render();
	void RenderEnd();
	void RenderBegin();

public:
	bool CreateDevice();
	bool CreateSwapChain();
	void SetUpViewPort();
	bool ScreenResize();
	void CreateDepthStencilView();
	void CreateSampleState();
private:

	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11Texture2D* mBackBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT			mViewPort;
	ID3D11SamplerState* mSamplerState = NULL;

	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mIndexBuffer;
	ID3D11Buffer* mConstantBuffer = NULL;

	

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;

	ID3DBlob* VSblob;
	ID3DBlob* _errBlob;

	D3D_DRIVER_TYPE				md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						m4xMsaaQuality = 0;
	bool						mEnable4xMsaa = false;
	int                         check = 0;

};

