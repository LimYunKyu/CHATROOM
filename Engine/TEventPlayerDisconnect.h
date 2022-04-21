#pragma once
#include "ThreadEvent.h"
class TEventPlayerDisconnect :
    public ThreadEvent
{
public:
    TEventPlayerDisconnect(int idx);
public:
    void Excute();

    int midx;
};

