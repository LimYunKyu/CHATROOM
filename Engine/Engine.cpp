#include "pch.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Material.h"
#include "BufferManager.h"
#include "Camera.h"
#include "Timer.h"
#include "PlayerScript.h"
#include "InputManager.h"
#include "Texture.h"
#include "SceneManager.h"
#include "ChatManager.h"
#include "ServerSession.h"
#include "Service.h"
#include "ThreadManager.h"
#include "GameObjectCollector.h"
#include "EventFromThreads.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"


Engine::Engine()
{
}

Engine::~Engine()
{
	GThreadManager->Join();

}

bool Engine::Initialize(WindowInfo& winfo)
{
	mWinfo = winfo;

	mGraphicsProcessor = make_shared<GraphcisProcessor>();
	if(!mGraphicsProcessor->Initialize())
		return false;

	ResourceManager::GetInstance()->Init();
	BufferManager::GetInstance()->Init();
	Timer::GetInstance()->Init();
	ChatManager::GetInstance()->Init();
	InputManager::GetInstance()->Init(WINFO.hWnd);

	StartConnectToServer();

	while (!isConnected.load())
		;

	SceneManager::GetInstance()->Init();
	





	return true;
}

bool Engine::Update()
{

	if (!isEnterGame)
		return true;

	if (!mGraphicsProcessor->Update())
		return false;
	InputManager::GetInstance()->Update();
	Timer::GetInstance()->Update();
	EventFromThreads::GetInstance()->ExcuteEvents();
	SceneManager::GetInstance()->Update();
	ChatManager::GetInstance()->Update();


	return true;
}

bool Engine::Render()
{
	if (!isEnterGame)
		return true;

	mGraphicsProcessor->RenderBegin();

	SceneManager::GetInstance()->Render();
	ChatManager::GetInstance()->Render();

	mGraphicsProcessor->RenderEnd();



	return true;
}

void Engine::StartConnectToServer()
{
	//서버 관련
	ServerPacketHandler::Init();

	service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>, // TODO : SessionManager 등
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

}



void Engine::ExitProgram()
{

	thread exitprogram([&]() {
		
		Protocol::C_PLAYER_DISCONNECT disconnectpkt;
		
		int pktid = GameObjectCollector::GetInstance()->GetPlayer()->GetServerToId();

		disconnectpkt.set_disconnect(true);
		disconnectpkt.set_id(pktid);

		auto sendBuffer = ServerPacketHandler::MakeSendBuffer(disconnectpkt);
		auto session = GameObjectCollector::GetInstance()->GetPlayer()-> GetSession();
		session->Send(sendBuffer);


		});
	exitprogram.detach();


}

bool Engine::ScreenResize()
{
	return mGraphicsProcessor->ScreenResize();
}

void Engine::SendText(CHAR text)
{
	InputManager::GetInstance()->ReceiveText(text);
}





