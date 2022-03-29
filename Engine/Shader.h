#pragma once
#include "Object.h"
class Shader :
    public Object
{
public:
    Shader();

public:
    void Render();
public:
    void CreateShader(const wstring& path,const string& vs = "VS_Main", const string& ps = "PS_Main");
    void CreateVertexShaderFile(const wstring& path, const string& name, const string& version);
    void CreatePixelShaderFile(const wstring& path, const string& name, const string& version);
    void BindShader();

private:
    ID3D11VertexShader* mVertexShader;
    ID3D11PixelShader* mPixelShader;
    ID3D11InputLayout* mInputLayout;
};

