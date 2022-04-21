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
	void StartConnectToServer();
	void SuccessConnect() { isConnected.store(true,memory_order_seq_cst); }
	void SuccessEnterGame() { isEnterGame = true; }


public:
	void ExitProgram();

public:
	bool ScreenResize();
	const WindowInfo GetWinfo() { return mWinfo; }
	shared_ptr<class GraphcisProcessor> GetGraphicsProcessor() { WRITE_LOCK return mGraphicsProcessor; }
	void SendText(CHAR text);
	ClientServiceRef GetServerService() { return service; }

private:
	WindowInfo Garbage = {};
	WindowInfo& mWinfo = Garbage;

	shared_ptr<class GraphcisProcessor> mGraphicsProcessor;

	

	
private:
	//Test

	atomic<bool> isConnected = false;
	bool isEnterGame = false;
	FontType*  mFontType;
	shared_ptr<class Texture> mFontTextre;
	ClientServiceRef service;
	USE_LOCK
};

