#include "pch.h"
#include "ChatScript.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "GameObject.h"
#include "Animator.h"
#include "Timer.h"
#include "Text.h"
#include "ChatManager.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"
#include "Engine.h"
#include "ServerSession.h"
#include "Service.h"
#include "GameObjectCollector.h"

void ChatScript::Init()
{

}

void ChatScript::Update()
{



}

void ChatScript::LateUpdate()
{

	if (InputManager::GetInstance()->GetButtonDown(VK_RETURN))
	{
		mChatBarOn = !mChatBarOn;
		InputManager::GetInstance()->SetChatOnState(mChatBarOn);
	}

	char* sentence = InputManager::GetInstance()->GetSentnece();
	int len = strlen(sentence);

	if (mChatBarOn)
	{
		//플레이어의 채팅 

		mChatBarBackground.lock()->SetAlive(true);

		char* sentence = InputManager::GetInstance()->GetSentnece();
		int len = strlen(sentence);


		for (int i = 0; i < mSentenceObjects.size(); i++)
		{
			mSentenceObjects[i].lock()->GetText()->SetSentence(sentence);
		}

	}
	else
	{
		mChatBarBackground.lock()->SetAlive(false);


		//auto speachBubble = ChatManager::GetInstance()->FindSpeachBubble(L"Player");
		//auto background = speachBubble->GetChildObjects()[0];
		//auto SentenceObjects = background->GetChildObjects();
		char* sentence = InputManager::GetInstance()->GetSentnece();
		int len = strlen(sentence);

		
		if (len != 0)
		{
			mChatTimerStart = true;
			mCurrentChatTime = 0.f;

	

			SendDataToServer(sentence);
			InputManager::GetInstance()->ResetSentence();

		}
		

	}

	/*if (mChatTimerStart)
	{
		if (mCurrentChatTime > mAliveChatTime)
		{
			mCurrentChatTime = 0.f;

			mChatTimerStart = false;

			auto speachBubble = ChatManager::GetInstance()->FindSpeachBubble(L"Player");
			auto background = speachBubble->GetChildObjects()[0];
			auto SentenceObjects = background->GetChildObjects();
			char* sentence = InputManager::GetInstance()->GetSentnece();

			for (int i = 0; i < SentenceObjects.size(); i++)
			{
				sentence[0] = 0;
				SentenceObjects[i]->GetText()->SetSentence(sentence);
			}

			

			for (auto child : speachBubble->GetChildObjects())
			{
				
				child->SetAlive(false);
			}

		}

		mCurrentChatTime += Timer::GetInstance()->GetDeltaTime();

	}*/


}

void ChatScript::SendDataToServer(char* sentence)
{
	Protocol::C_CHAT chatPkt;
	int idx = GameObjectCollector::GetInstance()->GetPlayer()->GetServerToId();
	chatPkt.set_msg(sentence);
	chatPkt.set_playerid(idx);
	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);




	GEngine->GetServerService()->Broadcast(sendBuffer);
	
}

void ChatScript::ShowSpeachBubble(char* sentence)
{
}



