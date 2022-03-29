#include "pch.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Material.h"
#include "BufferManager.h"
#include "Camera.h"
#include "Timer.h"
#include "PlayerScript.h"
#include "InputManager.h"
#include "Texture.h"

Engine::Engine()
{
}

Engine::~Engine()
{


}

bool Engine::Initialize(WindowInfo& winfo)
{
    mWinfo = winfo;
    mGraphicsProcessor = make_shared<GraphcisProcessor>();
    if (!mGraphicsProcessor->Initialize())
        return false;


   


    ResourceManager::GetInstance()->Init();
    BufferManager::GetInstance()->Init();
    Timer::GetInstance()->Init();
    InputManager::GetInstance()->Init(WINFO.hWnd);



#pragma region Font

  

    {
        LoadFontDataFromFile("../Texture/Font/fontdata.txt", L"..\\Texture\\Font\\font.dds");
        mFont = make_shared<GameObject>();
        mFont->SetObjectName(L"Font");
        shared_ptr<Transform> CTransform = make_shared<Transform>();
        CTransform->SetPosition({ -50.0f,0.0f,1.f });
        CTransform->SetScale({ 1.f,1.f,1.f });
        mFont->AddComponent(CTransform);
        shared_ptr<Animator> CAnimator = make_shared<Animator>();

        shared_ptr<Mesh> CMesh = make_shared<Mesh>();
        CreateFontBuffer(CMesh, 16);
        UpdateSentence(CMesh, "Hello World", 50, 50);

        CAnimator->SetMesh(CMesh);
        CAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Player"));
        CAnimator->SetState(ANIM_STATE::BACKGROUND);
        ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Font\\font.dds");
        mFont->AddComponent(CAnimator);
    }

    




#pragma endregion

    





#pragma region BackGround

    {
        mBackGround = make_shared<GameObject>();
        mBackGround->SetObjectName(L"BackGroubd");

        shared_ptr<Transform> CTransform = make_shared<Transform>();
        CTransform->SetPosition({ 0.0f,0.0f,10.f });
        CTransform->SetScale({ 1344.f,840.0f,1.0f });
        CTransform->SetAddRotation({ 0.f,0.f,0.f });
        mBackGround->AddComponent(CTransform);

        shared_ptr<Animator> CAnimator = make_shared<Animator>();


        CAnimator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
        CAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"BackGround"));
        ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CAnimator, ANIM_STATE::BACKGROUND,L"..\\Texture\\BackGround\\BackGround1.png");
        CAnimator->SetState(ANIM_STATE::BACKGROUND);

        mBackGround->AddComponent(CAnimator);


    }




#pragma endregion




#pragma region Player

    {
        mPlayer = make_shared<GameObject>();
        mPlayer->SetObjectName(L"Player");

        shared_ptr<Transform> CTransform = make_shared<Transform>();
        CTransform->SetPosition({ 0,0.0f,0.3f });
        CTransform->SetScale({ 200.f,200,1.0f });
        CTransform->SetAddRotation({ 0.f,0.f,0.f });
        mPlayer->AddComponent(CTransform);

        shared_ptr<Animator> CAnimator = make_shared<Animator>();

       
        CAnimator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
        CAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Player"));
        ResourceManager::GetInstance()->LoadAnimTextures(CAnimator, ANIM_STATE::IDLE, 17, L"..\\Texture\\Player\\Ranger\\Idle");
        ResourceManager::GetInstance()->LoadAnimTextures(CAnimator, ANIM_STATE::WALK, 7, L"..\\Texture\\Player\\Ranger\\Walk");
      


        mPlayer->AddComponent(CAnimator);

        shared_ptr<Camera> CCamera = make_shared<Camera>();
        CCamera->SetMapSize(1344.f, 840.f);
        mPlayer->AddComponent(CCamera);

        mPlayer->AddComponent(make_shared<PlayerScript>());

       
        
    
    }
   

    

#pragma endregion


   
   
#pragma region Camera

  /*  {
        mCamera = make_shared<GameObject>();
        mCamera->SetObjectName(L"Camera");
        mCamera->SetParentGameObject(mPlayer);

        shared_ptr<Transform> CTransform = make_shared<Transform>();
        CTransform->SetPosition({ 500.0f,0.0f,0.f });

        mCamera->AddComponent(CTransform);
        mCamera->AddComponent(make_shared<Camera>());
    
    }*/
   

#pragma endregion




    return true;
}

bool Engine::Update()
{
    if (!mGraphicsProcessor->Update())
        return false;
    InputManager::GetInstance()->Update();
    Timer::GetInstance()->Update();


    mBackGround->Update();
    mPlayer->Update();
   // mCamera->Update();
    mFont->Update();


    mBackGround->LateUpdate();
    mPlayer->LateUpdate(); 
   // mCamera->LateUpdate();
    mFont->LateUpdate();
    return true;
}

bool Engine::Render()
{
    mGraphicsProcessor->RenderBegin();
   

   

    mBackGround->Render();
    mPlayer->Render();
    mFont->Render();
    mGraphicsProcessor->RenderEnd();
  
   
    
    return true;
}



bool Engine::ScreenResize()
{
    return mGraphicsProcessor->ScreenResize();
}

void Engine::CreateFontBuffer(shared_ptr<class Mesh> _mesh, int FontLength)
{
    Vertex* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;
    int i;

    int vertexcount = 6 * FontLength;
    int indexcount = 6 * FontLength;
    int length = FontLength;


    
    vertices = new Vertex[vertexcount];

    indices = new unsigned long[indexcount];

    memset(vertices, 0, (sizeof(Vertex) * vertexcount));


   /* for (int i = 0; i < vertexcount; i++)
    {

        if (i % 4 == 1)
        {
            vertices[i].Pos = { -1.f,1.f,1.f };
            vertices[i].Tex = { 0.f,0.f };
        }
        else if (i % 4 == 2)
        {
            vertices[i].Pos = { 1.f,1.f,1.f };
            vertices[i].Tex = { 1.f,0.f };
        }
        else if (i % 4 == 3)
        {
            vertices[i].Pos = { 1.f,-1.f,1.f };
            vertices[i].Tex = { 1.f,1.f };
        }
        else if (i % 4 == 0)
        {
            vertices[i].Pos = { -1.f,-1.f,1.f };
            vertices[i].Tex = { 0.f,1.f };
        }
    }*/
   


    for (i = 0; i < indexcount; i++)
    {
        indices[i] = i;
    }

    // Set up the description of the dynamic vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexcount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    ID3D11Buffer* meshVertexBuffer;

    // Create the vertex buffer.
    result = GetGraphicsProcessor()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &meshVertexBuffer);
    
    _mesh->SetVertexBuffer(meshVertexBuffer, vertexcount);

    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * indexcount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    ID3D11Buffer* meshIndexBuffer = _mesh->GetIndexBuffer();

    // Create the index buffer.
    result = GetGraphicsProcessor()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &meshIndexBuffer);
    _mesh->SetInexBuffer(meshIndexBuffer, indexcount);

    // Release the vertex array as it is no longer needed.
    delete[] vertices;
    vertices = 0;

    // Release the index array as it is no longer needed.
    delete[] indices;
    indices = 0;

   
}

bool Engine::UpdateSentence(shared_ptr<class Mesh> _mesh, const char* text, int positionX, int positionY)
{

    int numLetters;
    Vertex* vertices;
    float drawX, drawY;
    HRESULT result;
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    Vertex* verticesPtr;

    numLetters = (int)strlen(text);




    // Check for possible buffer overflow.
    if (numLetters > 16)
    {
        return false;
    }

    // Create the vertex array.
    vertices = new Vertex[96];
    if (!vertices)
    {
        return false;
    }
    memset(vertices, 0, (sizeof(Vertex) * 96));


    drawX = 0.f; //(float)(((WINFO.ClientWidth / 2) * -1) + positionX);
    drawY = 0.f;// (float)((WINFO.ClientHeight / 2) - positionY);

   

    // Use the font class to build the vertex array from the sentence text and sentence draw location.
    BuildVertexArray((void*)vertices, text, drawX, drawY);

    // Lock the vertex buffer so it can be written to.
    result = GetGraphicsProcessor()->GetDeviceContext()->Map(_mesh->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    if (FAILED(result))
    {
        return false;
    }
   
  

    // Get a pointer to the data in the vertex buffer.
    verticesPtr = (Vertex*)mappedResource.pData;

    // Copy the data into the vertex buffer.
    memcpy(verticesPtr, (void*)vertices, (sizeof(Vertex) * 96));

    // Unlock the vertex buffer.
    GetGraphicsProcessor()->GetDeviceContext()->Unmap(_mesh->GetVertexBuffer(), 0);

    // Release the vertex array as it is no longer needed.
    delete[] vertices;
    vertices = 0;
    return true;
}

void Engine::BuildVertexArray(void* vertices, const char* sentence, float drawX, float drawY)
{
    Vertex* vertexPtr;
    int numLetters, index, i, letter;

   
    // Coerce the input vertices into a VertexType structure.
    vertexPtr = (Vertex*)vertices;
   
    // Get the number of letters in the sentence.
    numLetters = (int)strlen(sentence);

    // Initialize the index to the vertex array.
    index = 0;
   
    // Draw each letter onto a quad.
    for (i = 0; i < numLetters; i++)
    {
        letter = ((int)sentence[i]) - 32;

        // If the letter is a space then just move over three pixels.
        if (letter == 0)
        {
            drawX = drawX + 3.0f;
        }
        else
        {
            // First triangle in quad.
            vertexPtr[index].Pos = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].left, 0.0f);
            index++;

            vertexPtr[index].Pos = XMFLOAT3((drawX + mFontType[letter].size), (drawY - 16), 0.0f);  // Bottom right.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].right, 1.0f);
            index++;

            vertexPtr[index].Pos = XMFLOAT3(drawX, (drawY - 16), 0.0f);  // Bottom left.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].left, 1.0f);
            index++;

            // Second triangle in quad.
            vertexPtr[index].Pos = XMFLOAT3(drawX, drawY, 0.0f);  // Top left.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].left, 0.0f);
            index++;

            vertexPtr[index].Pos = XMFLOAT3(drawX + mFontType[letter].size, drawY, 0.0f);  // Top right.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].right, 0.0f);
            index++;

            vertexPtr[index].Pos = XMFLOAT3((drawX + mFontType[letter].size), (drawY - 16), 0.0f);  // Bottom right.
            vertexPtr[index].Tex = XMFLOAT2(mFontType[letter].right, 1.0f);
            index++;

            // Update the x location for drawing by the size of the letter and one pixel.
            drawX = drawX + mFontType[letter].size + 1.0f;

        }
    }

  
}

bool Engine::LoadFontDataFromFile(const char* fontFilename, const WCHAR* textureFilename)
{
    if (!LoadFontData(fontFilename))
    {
        return false;
    }

    mFontTextre = make_shared<Texture>();
    mFontTextre->Load(textureFilename);


    return true;
}

bool Engine::LoadFontData(const char* filename)
{
    ifstream fin;
    int i;
    char temp;


    // Create the font spacing buffer.
    mFontType = new FontType[95];
    if (!mFontType)
    {
        return false;
    }

    // Read in the font size and spacing between chars.
    fin.open(filename);
    if (fin.fail())
    {
        return false;
    }

    // Read in the 95 used ascii characters for text.
    for (i = 0; i < 95; i++)
    {
        fin.get(temp);
        while (temp != ' ')
        {
            fin.get(temp);
        }
        fin.get(temp);
        while (temp != ' ')
        {
            fin.get(temp);
        }

        fin >> mFontType[i].left;
        fin >> mFontType[i].right;
        fin >> mFontType[i].size;
    }

    // Close the file.
    fin.close();

    return true;

}



