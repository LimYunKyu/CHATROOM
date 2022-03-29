#pragma once
enum class CONSTANT_BUFFER_TYPE : UINT8
{
	TRANSFORM,
	MATERIAL,
	END
};

enum
{
	CONSTANT_BUFFER_COUNT = static_cast<UINT8>(CONSTANT_BUFFER_TYPE::END)
};

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Init(CBV_REGISTER reg, UINT32 size, UINT32 count);
	void PushData(void* buffer);
	void SetGlobalData(void* buffer);



private:
	void CreateBuffer();

private:
	ID3D11Buffer* mConstantBuffer;
	BYTE* mMappedBuffer = nullptr;

	CBV_REGISTER			mCBVRegisterNum = {};
	UINT32					mCBVSize;
	UINT32					mCBVCount;
};
