#include "pch.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Room.h"
#include "GameSession.h"
#include "GameSessionManager.h"


PacketHandlerFunc GPacketHandler[UINT16_MAX];

// ���� ������ �۾���

bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt)
{
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	// TODO : Validation üũ

	Protocol::S_LOGIN loginPkt;
	loginPkt.set_success(true);

	// DB���� �÷��� ������ �ܾ�´�
	// GameSession�� �÷��� ������ ���� (�޸�)

	// ID �߱� (DB ���̵� �ƴϰ�, �ΰ��� ���̵�)
	static Atomic<uint64> idGenerator = 1;

	{
		auto player = loginPkt.add_players();
		player->set_name(u8"Player");
		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);
		player->set_playerstate(Protocol::PLAYER_STATE_IDLE);
		player->set_posx(0);
		player->set_posy(0);
		player->set_id(idGenerator);
		
		

		PlayerRef playerRef = MakeShared<Player>();
		playerRef->playerId = idGenerator++;
		playerRef->name = player->name();
		playerRef->type = player->playertype();
		playerRef->ownerSession = gameSession;
		

		gameSession->_players.push_back(playerRef);
	}



	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt)
{

	//cout << "���Դ�" << endl;
	//���ӿ� �����⸦ ��û�� Ŭ�󿡰� �����ֱ�
	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	uint64 index = pkt.playerindex();
	// TODO : Validation

	PlayerRef player = gameSession->_players[index]; // READ_ONLY?
	GRoom.Enter(player); // WRITE_LOCK

	Protocol::S_ENTER_GAME enterGamePkt;
	enterGamePkt.set_success(true);
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePkt);
	player->ownerSession->Send(sendBuffer);
	

	//�̿��� Ŭ��鿡�Դ� ���ο� Ŭ�� ���Դٰ� �˷��ֱ�

	Protocol::S_OTHER_PLAYER_ENTER enterOtherPkt;
	enterOtherPkt.set_id(player->playerId);
	enterOtherPkt.set_posx(0);
	enterOtherPkt.set_posy(0);

	auto othersendBuffer = ClientPacketHandler::MakeSendBuffer(enterOtherPkt);

	GRoom.BroadcastEnter(othersendBuffer, player->playerId);


	return true;
}

bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt)
{
	std::cout << pkt.msg() << endl;

	Protocol::S_CHAT chatPkt;
	chatPkt.set_playerid(pkt.playerid());
	chatPkt.set_msg(pkt.msg());
	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPkt);

	GRoom.Broadcast(sendBuffer); // WRITE_LOCK

	return true;
}

bool Handle_C_PLAYER_INFO(PacketSessionRef& session, Protocol::C_PLAYER_INFO& pkt)
{


	int id = pkt.id();
	int posX = pkt.posx();
	int posY = pkt.posy();
	
	/*std::cout << id << " : posX = " << pkt.posx() << endl;
	std::cout << id << " : posY = " << pkt.posy() << endl;*/
	auto player = GRoom.FindPlayer(id);
	player->posX = posX;
	player->posY = posY;
	

	Protocol::S_OTHER_PLAYER_INFO otherinfo;
	otherinfo.set_id(id);
	otherinfo.set_posx(posX);
	otherinfo.set_posy(posY);
	otherinfo.set_playerdir(pkt.playerdir());
	otherinfo.set_playerstate(pkt.playerstate());

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(otherinfo);
	
	GRoom.BroadcastExceptOwner(sendBuffer,id);



	return true;
}

bool Handle_C_OTHER_PLAYER_INFO(PacketSessionRef& session, Protocol::C_OTHER_PLAYER_INFO& pkt)
{

	cout << pkt.id() << endl;

	return true;
}

bool Handle_C_OTHER_PLAYER_ENTER(PacketSessionRef& session, Protocol::C_OTHER_PLAYER_ENTER& pkt)
{
	cout << pkt.numofother() << endl;


	return true;
}

bool Handle_C_PLAYER_DISCONNECT(PacketSessionRef& session, Protocol::C_PLAYER_DISCONNECT& pkt)
{


	Protocol::S_PLAYER_DISCONNECT disconnectpkt;
	disconnectpkt.set_id(pkt.id());
	disconnectpkt.set_disconnect(true);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(disconnectpkt);

	GRoom.BroadcastDisconnect(sendBuffer, pkt.id());

	GameSessionRef gameSession = static_pointer_cast<GameSession>(session);
	GSessionManager.Remove(gameSession);

	return true;
}
