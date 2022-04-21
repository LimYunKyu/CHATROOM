#pragma once

class Room
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);
	void BroadcastExceptOwner(SendBufferRef sendBuffer, int index);
	void BroadcastEnter(SendBufferRef sendBuffer, int index);
	void BroadcastDisconnect(SendBufferRef sendBuffer, int index);

public:
	PlayerRef FindPlayer(int key) { return _players[key]; }

private:
	USE_LOCK;
	map<uint64, PlayerRef> _players;
};

extern Room GRoom;