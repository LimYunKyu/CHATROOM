#pragma once
#include "Object.h"
class Texture :
    public Object
{

public:
    Texture();
public:
    virtual void Load(const wstring& path);
    ID3D11ShaderResourceView* GetSRV() { return mSRV; }

private:
    ID3D11ShaderResourceView* mSRV;
};

