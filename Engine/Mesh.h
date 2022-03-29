#pragma once
#include "Object.h"
class Mesh :
    public Object
{
public:
    Mesh();
    ~Mesh();
public:
    void Create(const vector<Vertex>& vertexBuffer, const vector<UINT>& indexBuffer);
    void CreateVertexBuffer(const vector<Vertex>& buffer);
    void CreateIndexBuffer(const vector<UINT>& buffer);
    

   

public:

    virtual void Render();

public:
    ID3D11Buffer*  GetVertexBuffer() { return mVertexBuffer; }
    ID3D11Buffer*  GetIndexBuffer() { return mIndexBuffer; }

    UINT32 GetVertexCount() { return mVertexCount; }
    UINT32 GetIndexCount() { return mIndexCount; }
public:
    //void SetInputLayout(ID3D11InputLayout* layout) { mInputLayout = layout; }
    void SetVertexBuffer(ID3D11Buffer* vbuffer, int vertexcount) { mVertexBuffer = vbuffer;  mVertexCount = vertexcount; }
    void SetInexBuffer(ID3D11Buffer* ibuffer, int indexcount) { mIndexBuffer = ibuffer;  mIndexCount = indexcount; }

private:
    ID3D11Buffer* mVertexBuffer;
    ID3D11Buffer* mIndexBuffer;
   // ID3D11InputLayout* mInputLayout;

    UINT32								mVertexCount = 0;
    UINT32								mIndexCount = 0;
};

