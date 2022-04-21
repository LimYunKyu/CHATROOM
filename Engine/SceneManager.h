#pragma once
class SceneManager
{
	DECLARE_SINGLE(SceneManager)

public:
	void Init();
	void Update();
	void Render();


public:
	void SetScene(shared_ptr<class Scene> _scene) { mCurrentScene = _scene; }
	shared_ptr<class Scene> GetScene() { return mCurrentScene; }
	void SetMapSize(XMFLOAT2 _size) { mCurrentMapSize = _size; }

public:
	const XMFLOAT2 GetCurrentMapSize() { return mCurrentMapSize; }


private:
	shared_ptr<class Scene> mCurrentScene;
	XMFLOAT2 mCurrentMapSize = {};
};

