#include "pch.h"
#include "Shader.h"
#include "Engine.h"
#include "GraphcisProcessor.h"

Shader::Shader() : Object(OBJECT_TYPE::SHADER)
{
}

void Shader::Render()
{
	BindShader();
}

void Shader::CreateShader(const wstring& path, const string& vs, const string& ps)
{
	CreateVertexShaderFile(path, vs, "vs_5_0");
	CreatePixelShaderFile(path, ps, "ps_5_0");

}

void Shader::CreateVertexShaderFile(const wstring& path, const string& name, const string& version)
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
		, name.c_str(), version.c_str(), compileFlag, 0, &VSblob, &ERRblob)))
	{
		::MessageBoxA(nullptr, "Vertex Shader Create Failed !", nullptr, MB_OK);
	}

	if (ERRblob)
	{
		OutputDebugStringA(reinterpret_cast<const char*>(ERRblob->GetBufferPointer()));
		MessageBox(WINFO.hWnd, L"error compiling shader", path.c_str(), MB_OK);
	}

	HR = GEngine->GetGraphicsProcessor()-> GetDevice()->CreateVertexShader(VSblob->GetBufferPointer(), VSblob->GetBufferSize(), NULL, &mVertexShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		
	};
	UINT numElements = ARRAYSIZE(layout);

	HR = GEngine->GetGraphicsProcessor()->GetDevice()-> CreateInputLayout(layout, numElements, VSblob->GetBufferPointer(), VSblob->GetBufferSize(), &mInputLayout);

	ReleaseCOM(VSblob);
	ReleaseCOM(ERRblob);
}

void Shader::CreatePixelShaderFile(const wstring& path, const string& name, const string& version)
{
	UINT32 compileFlag = 0;
#ifdef _DEBUG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT HR;
	ID3DBlob* PSblob;
	ID3DBlob* ERRblob;


	if (FAILED(HR = ::D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, name.c_str(), version.c_str(), compileFlag, 0, &PSblob, &ERRblob)))
	{
		::MessageBoxA(nullptr, "Pixel Shader Create Failed !", nullptr, MB_OK);
	}

	HR = GEngine->GetGraphicsProcessor()->GetDevice()-> CreatePixelShader(PSblob->GetBufferPointer(), PSblob->GetBufferSize(), NULL, &mPixelShader);
	ReleaseCOM(PSblob);
	ReleaseCOM(ERRblob);
}

void Shader::BindShader()
{

	GEngine->GetGraphicsProcessor()->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);

	GEngine->GetGraphicsProcessor()->GetDeviceContext()->IASetInputLayout(mInputLayout);


}
