#pragma once
#include "Scene.h"


class Dungeon : public Scene
{
public:
	Dungeon();
public:
	void Init();
	void LateInit();
	void Update();
	void LateUpdate();
	void Render();

};

