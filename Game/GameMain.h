#pragma once
class GameMain
{
public:
	GameMain();
	~GameMain();
public:
	bool Initialize(WindowInfo& info);
	bool Update();
	bool Render();

	bool ScreenResize();

};

