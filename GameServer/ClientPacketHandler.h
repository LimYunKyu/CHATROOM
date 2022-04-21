#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : uint16
{
	PKT_C_LOGIN = 1000,
	PKT_S_LOGIN = 1001,
	PKT_C_ENTER_GAME = 1002,
	PKT_S_ENTER_GAME = 1003,
	PKT_C_CHAT = 1004,
	PKT_S_CHAT = 1005,
	PKT_C_PLAYER_INFO = 1006,
	PKT_S_PLAYER_INFO = 1007,
	PKT_C_OTHER_PLAYER_INFO = 1008,
	PKT_S_OTHER_PLAYER_INFO = 1009,
	PKT_C_OTHER_PLAYER_ENTER = 1010,
	PKT_S_OTHER_PLAYER_ENTER = 1011,
	PKT_C_PLAYER_DISCONNECT = 1012,
	PKT_S_PLAYER_DISCONNECT = 1013,
};

// Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
bool Handle_C_LOGIN(PacketSessionRef& session, Protocol::C_LOGIN& pkt);
bool Handle_C_ENTER_GAME(PacketSessionRef& session, Protocol::C_ENTER_GAME& pkt);
bool Handle_C_CHAT(PacketSessionRef& session, Protocol::C_CHAT& pkt);
bool Handle_C_PLAYER_INFO(PacketSessionRef& session, Protocol::C_PLAYER_INFO& pkt);
bool Handle_C_OTHER_PLAYER_INFO(PacketSessionRef& session, Protocol::C_OTHER_PLAYER_INFO& pkt);
bool Handle_C_OTHER_PLAYER_ENTER(PacketSessionRef& session, Protocol::C_OTHER_PLAYER_ENTER& pkt);
bool Handle_C_PLAYER_DISCONNECT(PacketSessionRef& session, Protocol::C_PLAYER_DISCONNECT& pkt);


class ClientPacketHandler
{
public:
	static void Init()
	{
		for (int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
		GPacketHandler[PKT_C_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_LOGIN>(Handle_C_LOGIN, session, buffer, len); };
		GPacketHandler[PKT_C_ENTER_GAME] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ENTER_GAME>(Handle_C_ENTER_GAME, session, buffer, len); };
		GPacketHandler[PKT_C_CHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_CHAT>(Handle_C_CHAT, session, buffer, len); };
		GPacketHandler[PKT_C_PLAYER_INFO] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_PLAYER_INFO>(Handle_C_PLAYER_INFO, session, buffer, len); };
		GPacketHandler[PKT_C_OTHER_PLAYER_INFO] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_OTHER_PLAYER_INFO>(Handle_C_OTHER_PLAYER_INFO, session, buffer, len); };
		GPacketHandler[PKT_C_OTHER_PLAYER_ENTER] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_OTHER_PLAYER_ENTER>(Handle_C_OTHER_PLAYER_ENTER, session, buffer, len); };
		GPacketHandler[PKT_C_PLAYER_DISCONNECT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_PLAYER_DISCONNECT>(Handle_C_PLAYER_DISCONNECT, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(Protocol::S_LOGIN& pkt) { return MakeSendBuffer(pkt, PKT_S_LOGIN); }
	static SendBufferRef MakeSendBuffer(Protocol::S_ENTER_GAME& pkt) { return MakeSendBuffer(pkt, PKT_S_ENTER_GAME); }
	static SendBufferRef MakeSendBuffer(Protocol::S_CHAT& pkt) { return MakeSendBuffer(pkt, PKT_S_CHAT); }
	static SendBufferRef MakeSendBuffer(Protocol::S_PLAYER_INFO& pkt) { return MakeSendBuffer(pkt, PKT_C_PLAYER_INFO); }
	static SendBufferRef MakeSendBuffer(Protocol::S_OTHER_PLAYER_INFO& pkt) { return MakeSendBuffer(pkt, PKT_S_OTHER_PLAYER_INFO); }
	static SendBufferRef MakeSendBuffer(Protocol::S_OTHER_PLAYER_ENTER& pkt) { return MakeSendBuffer(pkt, PKT_S_OTHER_PLAYER_ENTER); }
	static SendBufferRef MakeSendBuffer(Protocol::S_PLAYER_DISCONNECT& pkt) { return MakeSendBuffer(pkt, PKT_S_PLAYER_DISCONNECT); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<typename T>
	static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
	{
		const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};