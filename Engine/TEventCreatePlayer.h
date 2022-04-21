#pragma once
#include "ThreadEvent.h"
class TEventCreatePlayer :
    public ThreadEvent
{
public:
    TEventCreatePlayer(int id, XMFLOAT3 pos, SessionRef _session);
    void Excute() override;

private:
    int pktid;
    XMFLOAT3 Pos;
    SessionRef session;

};

