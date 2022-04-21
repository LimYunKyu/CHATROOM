#pragma once
#include "MonoBehaviour.h"
class SpeachBubbleScript :
    public MonoBehaviour
{

    
    void LateUpdate();
public:
    void SetSentence(string sentence);
    void AddSentenceObj(shared_ptr<class GameObject> obj) { mSenctenceVec.push_back(obj); }
    void SetBackGround(shared_ptr<class GameObject> obj) { mBackGround = obj; }

public:
    vector<shared_ptr<class GameObject>> mSenctenceVec;
    shared_ptr<class GameObject> mBackGround;
    string mCurrentSentence;
    bool mAlive = false;
    float mStartTime = 0.f;
    float mAliveTime = 3.f;
};

