#pragma once


class GameObjectCollector
{

	DECLARE_SINGLE(GameObjectCollector)


public:
	void Update();
	void LateUpdate();
	void Render();

public:
	shared_ptr<class GameObject> GetPlayer() { return mPlayer; }
	shared_ptr<class GameObject> GetOtherPlayer(int idx) {READ_LOCK return mOtherPlayer[idx]; }
	shared_ptr<class GameObject> FindOtherPlayer(uint64 id) { return mOtherPlayer[id]; }
	uint64 GetNumOfOtherPlayer() { return mOtherPlayer.size(); }

public:
	void SetPlayer(shared_ptr<class GameObject> player) { mPlayer = player; }
	void AddOtherPlayer(shared_ptr<class GameObject> other, uint64 id);
	void DeleteOtherPlayer(int idx) { mOtherPlayer[idx] = nullptr; mOtherPlayer.erase(idx); }


private:

	USE_LOCK
	shared_ptr<class GameObject> mPlayer;
	map<uint64, shared_ptr<class GameObject>>mOtherPlayer;
	

};

