#pragma once
class ChatManager
{
	DECLARE_SINGLE(ChatManager)


public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();

public:
	void CreateChatObject();
	
	void RegisterSpeachBubble(int idx, shared_ptr<class GameObject> bubble) { mChatObjectMap[idx] = bubble; }
	void BroadCastSentence(int idx, string message);
	void DeleteSpeachBubbleObj(int idx) { mChatObjectMap[idx] = nullptr; mChatObjectMap.erase(idx); }

	shared_ptr<class GameObject> GetChatObject() { return mChatObject; }
	
	shared_ptr<class GameObject> FindSpeachBubble(int idx) { return mChatObjectMap[idx]; }
private:
	

	shared_ptr<class GameObject> mChatObject;
	shared_ptr<vector<FontType>> fonttypevec;
	shared_ptr<class ChatScript> chatScript;
	map<int, shared_ptr<class GameObject>> mChatObjectMap;
};

