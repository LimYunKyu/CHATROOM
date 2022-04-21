#pragma once
class EventFromThreads
{


	DECLARE_SINGLE(EventFromThreads)

public:
	void RegisterEvent(shared_ptr<class ThreadEvent> _event);
	void ExcuteEvents();

private:
	USE_LOCK
	queue<shared_ptr<class ThreadEvent>> eventqueue;

};

