#include "pch.h"
#include "EventFromThreads.h"
#include "ThreadEvent.h"

void EventFromThreads::RegisterEvent(shared_ptr<class ThreadEvent> _event)
{
	WRITE_LOCK
	eventqueue.push(_event);

}

void EventFromThreads::ExcuteEvents()
{
	
	while (eventqueue.size())
	{
		auto _event = eventqueue.front();
		_event->Excute();
		eventqueue.pop();

	}

}
