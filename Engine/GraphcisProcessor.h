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

	bool CreateDeviceAndSwapChain();

	void SetUpViewPort();
	bool ScreenResize();
	void CreateDepthStencilView();
	void CreateSampleState();


public:
	ID3D11Device* GetDevice() { return mDevice; }
	ID3D11DeviceContext* GetDeviceContext();
	
	
private:

	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	ID3D11Texture2D* mBackBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT			mViewPort;
	ID3D11SamplerState* mSamplerState = NULL;

	
	ID3D11DepthStencilState* mDepthStencilState;

	

	IDXGIDevice* mdxgiDevice;
	IDXGIAdapter* mdxgiAdapter;
	IDXGIFactory* mdxgiFactory;
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader* mPixelShader;
	ID3DBlob* VSblob;
	ID3DBlob* _errBlob;
	ID3D11InputLayout* mInputLayout;
	D3D_DRIVER_TYPE				md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT						m4xMsaaQuality = 0;
	bool						mEnable4xMsaa = false;
	int                         check = 0;

	D3D_DRIVER_TYPE         mdriverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       mfeatureLevel = D3D_FEATURE_LEVEL_11_0;
	UINT32								mVertexCount = 0;
	UINT32								mIndexCount = 0;



	USE_LOCK
};

