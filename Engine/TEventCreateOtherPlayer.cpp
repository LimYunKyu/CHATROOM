#include "pch.h"
#include "TEventCreateOtherPlayer.h"
#include "ResourceManager.h"
#include "GameObjectCollector.h"

TEventCreateOtherPlayer::TEventCreateOtherPlayer(int id, XMFLOAT3 pos) : pktid(id),Pos(pos)
{


}

void TEventCreateOtherPlayer::Excute()
{
	auto otherPlayer = ResourceManager::GetInstance()->CreateOtherPlayer(pktid);
	XMFLOAT3 pos = Pos;

	otherPlayer->GetTransform()->SetPosition(pos);

	
	GameObjectCollector::GetInstance()->AddOtherPlayer(otherPlayer, pktid);

}
