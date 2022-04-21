#include "pch.h"
#include "TEventCreatePlayer.h"
#include "ResourceManager.h"
#include "GameObjectCollector.h"

TEventCreatePlayer::TEventCreatePlayer(int id, XMFLOAT3 pos, SessionRef _session) :pktid(id),Pos(pos),session(_session)
{
}

void TEventCreatePlayer::Excute()
{
	auto player =  ResourceManager::GetInstance()->CreatePlayer(pktid,session);
	GameObjectCollector::GetInstance()->SetPlayer(player);
}
