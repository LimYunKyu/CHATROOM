#include "pch.h"
#include "ServerTransceiver.h"
#include "Session.h"
#include "ServerPacketHandler.h"
#include "GameObject.h"
#include "Animator.h"
#include "Transform.h"
#include "Engine.h"
#include "Service.h"
#include "Timer.h"
#include <thread>

ServerTransceiver::ServerTransceiver() : Component(COMPONENT_TYPE::SERVERTRANSCEIVER)
{
	
}

ServerTransceiver::~ServerTransceiver()
{

}

void ServerTransceiver::LateUpdate()
{

	SendDataToServer();

}

void ServerTransceiver::SendDataToServer()
{


	if (mEllapseTime < mSendTime)
	{
		mEllapseTime += Timer::GetInstance()->GetDeltaTime();
		return;
	}
	
	mEllapseTime = 0.0f;
	

	//데이터를 보내기
	thread SendData([&]() {
		
		Protocol::C_PLAYER_INFO pinfoPkt;
		pinfoPkt.set_id(mGameObject.lock()->GetServerToId());
		auto pos = mGameObject.lock()->GetTransform()->GetWorldPosition();
		pinfoPkt.set_posx(pos.x);
		pinfoPkt.set_posy(pos.y);

		auto pAnimator = mGameObject.lock()->GetAnimator();
		auto pAnimState = pAnimator->GetAnimState();

		Protocol::PlayerState pstatepkt;
		switch (pAnimState)
		{
		case ANIM_STATE::IDLE :
			pstatepkt = Protocol::PlayerState::PLAYER_STATE_IDLE;
			break;
		case ANIM_STATE::WALK:
			pstatepkt = Protocol::PlayerState::PLAYER_STATE_WALK;
			break;
		default:
			break;
		}

		pinfoPkt.set_playerstate(pstatepkt);


		auto pDirState = pAnimator->GetDirState();

		Protocol::PlayerDirection pdirpkt;
		switch (pDirState)
		{
		case ANIM_DIRECTION::LEFT:
			pdirpkt = Protocol::PlayerDirection::PLAYER_STATE_LEFT;
			break;
		case ANIM_DIRECTION::RIGHT:
			pdirpkt = Protocol::PlayerDirection::PLAYER_DIR_RIGHT;
			break;
		default:
			break;
		}

		pinfoPkt.set_playerdir(pdirpkt);

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(pinfoPkt);
		auto session = mGameObject.lock()->GetSession();
		session->Send(sendBuffer);
		});

	SendData.detach();

}
