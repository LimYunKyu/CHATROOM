#pragma once
class Engine
{
public:
	Engine();
	~Engine();
public:
	bool Initialize(WindowInfo& winfo);
	bool Update();
	bool Render();

public:
	bool ScreenResize();
	const WindowInfo GetWinfo() { return mWinfo; }

private:
	WindowInfo Garbage = {};
	WindowInfo& mWinfo = Garbage;

	shared_ptr<class GraphcisProcessor> mGraphicsProcessor;

};

