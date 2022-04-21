#include "pch.h"
#include "TEventPlayerDisconnect.h"
#include "GameObjectCollector.h"
#include "ChatManager.h"


TEventPlayerDisconnect::TEventPlayerDisconnect(int idx)
{
	midx = idx;
}

void TEventPlayerDisconnect::Excute()
{
	GameObjectCollector::GetInstance()->DeleteOtherPlayer(midx);
	ChatManager::GetInstance()->DeleteSpeachBubbleObj(midx);
}
