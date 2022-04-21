#include "pch.h"
#include "GameMain.h"
#include "Engine.h"




GameMain::GameMain()
{
}

GameMain::~GameMain()
{
}

bool GameMain::Initialize(WindowInfo& info)
{
    return GEngine->Initialize(info);;
}

bool GameMain::Update()
{
    return GEngine->Update();
}

bool GameMain::Render()
{
    return GEngine->Render();
}

bool GameMain::ScreenResize()
{
    return GEngine->ScreenResize();
}

void GameMain::SendText(TCHAR text)
{
    GEngine->SendText(text);

}

void GameMain::PleaseDisconnect()
{

    GEngine->ExitProgram();
}
