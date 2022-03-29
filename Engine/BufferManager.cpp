#include "pch.h"
#include "BufferManager.h"
#include "Material.h"


void BufferManager::Init()
{
	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(TransformParams), 1);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 1);


}

void BufferManager::CreateConstantBuffer(CBV_REGISTER reg, UINT32 bufferSize, UINT32 count)
{

	

	UINT8 typeInt = static_cast<UINT8>(reg);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, bufferSize, count);
	mConstantBuffers.push_back(buffer);

}
