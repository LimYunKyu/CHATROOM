#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"
#include "Protocol.pb.h"
#include "ClientPacketHandler.h"

Room GRoom;

void Room::Enter(PlayerRef player)
{
	WRITE_LOCK;
	_players[player->playerId] = player;
}

void Room::Leave(PlayerRef player)
{
	WRITE_LOCK;
	_players.erase(player->playerId);
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (auto& p : _players)
	{
		p.second->ownerSession->Send(sendBuffer);
	}
}

void Room::BroadcastExceptOwner(SendBufferRef sendBuffer , int index)
{
	WRITE_LOCK;
	for (auto& p : _players)
	{
		if (p.first == index)
			continue;

		p.second->ownerSession->Send(sendBuffer);
		//cout << "力寇等 index id : " <<index<< endl;
	}

	
}

void Room::BroadcastEnter(SendBufferRef sendBuffer, int index)
{


	//cout << "拌加 父电促" << endl;
	WRITE_LOCK;

	auto player = FindPlayer(index);

	
	for (auto& p : _players)
	{
		if (p.first == index)
		{

			continue;

		}

		p.second->ownerSession->Send(sendBuffer);

		Protocol::S_OTHER_PLAYER_ENTER otherinfo;
		otherinfo.set_id(p.second->playerId);
		otherinfo.set_posx(p.second->posX);
		otherinfo.set_posy(p.second->posY);

		auto othersendBuffer = ClientPacketHandler::MakeSendBuffer(otherinfo);

		player->ownerSession->Send(othersendBuffer);

		
	}



}

void Room::BroadcastDisconnect(SendBufferRef sendBuffer, int index)
{

	WRITE_LOCK;
	for (auto& p : _players)
	{
		if (p.first == index)
			continue;

		p.second->ownerSession->Send(sendBuffer);
		//cout << "力寇等 index id : " <<index<< endl;
	}
	_players.erase(index);
}
