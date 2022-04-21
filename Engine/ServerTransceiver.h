#pragma once
#include "Component.h"
#include "Protocol.pb.h"
class ServerTransceiver :
	public Component
{
public:
	ServerTransceiver();
	virtual ~ServerTransceiver();
public:
	 void LateUpdate();
	 void SendDataToServer();
private:
	float mSendTime = 0.02f;
	float mEllapseTime = 0.0f;
	USE_LOCK
};

