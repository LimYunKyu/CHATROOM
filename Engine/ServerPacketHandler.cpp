#include "pch.h"
#include "ServerPacketHandler.h"
#include "Engine.h"
#include "GameObjectCollector.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "ChatManager.h"
#include "TEventCreateOtherPlayer.h"
#include "EventFromThreads.h"
#include "TEventPlayerDisconnect.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
{
	if (pkt.success() == false)
		return true;


	// 캐릭터 생성창
	
	auto ServerId = pkt.players().Get(0).id();
	auto player = ResourceManager::GetInstance()->CreatePlayer(ServerId, session);
	//player->SetServerToId(ServerId);
	GameObjectCollector::GetInstance()->SetPlayer(player);
	player->SetSession(session);

	GEngine->SuccessConnect();


	// 입장 UI 버튼 눌러서 게임 입장
	Protocol::C_ENTER_GAME enterGamePkt;
	enterGamePkt.set_playerindex(0); // 첫번째 캐릭터로 입장
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
{

	if (pkt.success())
		GEngine->SuccessEnterGame();
	// TODO
	return true;
}

bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
{
	int id = pkt.playerid();
	string message = pkt.msg();
	
	ChatManager::GetInstance()->BroadCastSentence(id, message);





	return true;
}

bool Handle_S_PLAYER_INFO(PacketSessionRef& session, Protocol::S_PLAYER_INFO& pkt)
{

	int serverid = pkt.id();
	int posx = pkt.posx();
	int posy = pkt.posy();
	

	return true;
}

bool Handle_S_OTHER_PLAYER_INFO(PacketSessionRef& session, Protocol::S_OTHER_PLAYER_INFO& pkt)
{

	int idx = pkt.id();
	auto other = GameObjectCollector::GetInstance()->GetOtherPlayer(idx);
	if (other.get() == nullptr)
		return true;

	XMFLOAT3 pos = {static_cast<float>(pkt.posx()),static_cast<float>(pkt.posy()),0.f };
	other->GetTransform()->SetPosition(pos);


	ANIM_STATE animstate;
	switch (pkt.playerstate())
	{
	case Protocol::PlayerState::PLAYER_STATE_IDLE:
		animstate = ANIM_STATE::IDLE;
		break;
	case Protocol::PlayerState::PLAYER_STATE_WALK:
		animstate = ANIM_STATE::WALK;
		break;
	default:
		break;
	}


	ANIM_DIRECTION animdir;

	switch (pkt.playerdir())
	{
	case Protocol::PlayerDirection::PLAYER_DIR_RIGHT:
		animdir = ANIM_DIRECTION::RIGHT;
		break;
	case Protocol::PlayerDirection::PLAYER_STATE_LEFT:
		animdir = ANIM_DIRECTION::LEFT;
		break;
	default:
		break;
	}

	other->GetAnimator()->SetDirection(animdir);
	other->GetAnimator()->SetState(animstate);




	return true;
}

bool Handle_S_OTHER_PLAYER_ENTER(PacketSessionRef& session, Protocol::S_OTHER_PLAYER_ENTER& pkt)
{

	//auto other = ResourceManager::GetInstance()->CreateOtherPlayer(pkt.id());

	XMFLOAT3 pos = { static_cast<float>(pkt.posx()),static_cast<float>(pkt.posy()),0.f };


	shared_ptr<TEventCreateOtherPlayer>_event = make_shared<TEventCreateOtherPlayer>(pkt.id(), pos);
	EventFromThreads::GetInstance()->RegisterEvent(_event);

	Protocol::C_OTHER_PLAYER_ENTER enterGamePkt;
	int num = GameObjectCollector::GetInstance()->GetNumOfOtherPlayer();
	enterGamePkt.set_numofother(pkt.id());
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
	session->Send(sendBuffer);


	return true;
}

bool Handle_S_PLAYER_DISCONNECT(PacketSessionRef& session, Protocol::S_PLAYER_DISCONNECT& pkt)
{

	if (pkt.disconnect())
	{
		shared_ptr<TEventPlayerDisconnect> tevent = make_shared<TEventPlayerDisconnect>(pkt.id());

		EventFromThreads::GetInstance()->RegisterEvent(tevent);
	}


	return true;
}


