#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Dungeon.h"

void SceneManager::Init()
{
	mCurrentScene = make_shared<Dungeon>();


}

void SceneManager::Update()
{
	mCurrentScene->Update();
	mCurrentScene->LateUpdate();
}


void SceneManager::Render()
{
	mCurrentScene->Render();
}
