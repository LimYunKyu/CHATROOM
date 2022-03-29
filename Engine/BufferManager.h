#pragma once
#include "ConstantBuffer.h"

class BufferManager
{
	DECLARE_SINGLE(BufferManager)

public:
	void Init();
	void CreateConstantBuffer(CBV_REGISTER reg, UINT32 bufferSize, UINT32 count);

	shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return mConstantBuffers[static_cast<UINT8>(type)]; }
private:
	vector<shared_ptr<ConstantBuffer>> mConstantBuffers;


};

