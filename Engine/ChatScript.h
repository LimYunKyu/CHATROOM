#pragma once
#include "MonoBehaviour.h"
#include "InputManager.h"

class ChatScript :
    public MonoBehaviour
{

public:

    void Init();
    void Update();
    void LateUpdate();

public: 
    void SetChatBarBackground(shared_ptr<class GameObject> _obj) { mChatBarBackground = _obj; }
    void SetSpeachBubble(shared_ptr<class GameObject> _obj) { mSpeachBubble = _obj; }
    void AddChatSentenceObject(shared_ptr<class GameObject> _obj) { mSentenceObjects.push_back(_obj); }
    void SendDataToServer(char* sentence);
    void ShowSpeachBubble(char* sentence);
private:
    shared_ptr<class GameObject> mSpeachBubble;
    weak_ptr<class GameObject> mChatBarBackground;
    vector<weak_ptr<class GameObject>> mSentenceObjects;

private:
    bool mChatBarOn = false;
    bool mChatTimerStart = false;
    float mAliveChatTime = 3.0f;
    float mCurrentChatTime = 0.f;
};

