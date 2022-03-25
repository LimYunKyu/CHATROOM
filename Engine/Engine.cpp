#include "pch.h"
#include "Engine.h"
#include "GraphcisProcessor.h"

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


    return true;
}

bool Engine::Update()
{
    if (!mGraphicsProcessor->Update())
        return false;
    return true;
}

bool Engine::Render()
{
   // mGraphicsProcessor->RenderBegin();
   

    //������ ���� �ڵ�
    mGraphicsProcessor->Render();

    //mGraphicsProcessor->RenderEnd();
  

    return true;
}



bool Engine::ScreenResize()
{
    return mGraphicsProcessor->ScreenResize();
}
