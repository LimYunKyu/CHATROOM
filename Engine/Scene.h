#pragma once

#include "Object.h"
class Scene : public Object
{

public:
	Scene();
public:
	virtual void Init();
	virtual void LateInit();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

protected:
	shared_ptr<class GameObject> mPlayer;
	shared_ptr<class GameObject> mBackGround;
	shared_ptr<class GameObject> mFont;

	
};

