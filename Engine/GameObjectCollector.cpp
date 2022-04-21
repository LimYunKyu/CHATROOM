#include "pch.h"
#include "GameObjectCollector.h"
#include "GameObject.h"

void GameObjectCollector::Update()
{
	
	mPlayer->Update();
	for (auto other : mOtherPlayer)
	{
		other.second->Update();
	}

}

void GameObjectCollector::LateUpdate()
{
	
	mPlayer->LateUpdate();
	for (auto other : mOtherPlayer)
	{
		other.second->LateUpdate();
	}
}

void GameObjectCollector::Render()
{
	
	mPlayer->Render();
	for (auto other : mOtherPlayer)
	{
		if (other.second.get() == nullptr)
			int a = 5;
		other.second->Render();
	}
}

void GameObjectCollector::AddOtherPlayer(shared_ptr<class GameObject> other, uint64 id)
{
	WRITE_LOCK
	mOtherPlayer[id] = other; 
}
