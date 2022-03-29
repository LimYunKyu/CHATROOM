#include "pch.h"
#include "ConstantBuffer.h"
#include "GraphcisProcessor.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	ReleaseCOM(mConstantBuffer)
}



void ConstantBuffer::Init(CBV_REGISTER reg, UINT32 size, UINT32 count)
{
	mCBVRegisterNum = reg;

	mCBVSize = (size + 255) & ~255;;
	mCBVCount = count;

	CreateBuffer();
}

void ConstantBuffer::CreateBuffer()
{
	HRESULT HR;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	// Create the constant buffers

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = mCBVSize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;



	HR = GEngine->GetGraphicsProcessor()->GetDevice()->CreateBuffer(&bd, NULL, &mConstantBuffer);
	if (FAILED(HR))
	{
		UINT8 registernum = static_cast<UINT8>(mCBVRegisterNum);
		string errmsg = "ConstantBuffer Create Failed ! Register No : " + std::to_string(registernum);
		::MessageBoxA(nullptr, errmsg.c_str(), nullptr, MB_OK);
	}

}



void ConstantBuffer::PushData(void* buffer)
{
	TransformParams* temp = static_cast<TransformParams*>(buffer);

	GEngine->GetGraphicsProcessor()->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, buffer, 0, 0);
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->VSSetConstantBuffers(static_cast<UINT8>(mCBVRegisterNum), 1, &mConstantBuffer);
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->PSSetConstantBuffers(static_cast<UINT8>(mCBVRegisterNum), 1, &mConstantBuffer);

}

void ConstantBuffer::SetGlobalData(void* buffer)
{
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, buffer, 0, 0);
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->VSSetConstantBuffers(static_cast<UINT8>(mCBVRegisterNum), 1, &mConstantBuffer);
	GEngine->GetGraphicsProcessor()->GetDeviceContext()->PSSetConstantBuffers(static_cast<UINT8>(mCBVRegisterNum), 1, &mConstantBuffer);
}

