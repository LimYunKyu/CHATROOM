#pragma once
#include "ThreadEvent.h"
class TEventCreateOtherPlayer :
    public ThreadEvent
{

public:
    TEventCreateOtherPlayer(int id, XMFLOAT3 pos);
    void Excute() override;

private:
    int pktid;
    XMFLOAT3 Pos;

};

