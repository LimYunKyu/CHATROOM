#pragma once
#include "Component.h"


enum class ANIM_STATE
{
    IDLE,
    WALK,
    BACKGROUND,
    FONT,

};

enum class ANIM_DIRECTION
{
    NONE,
    LEFT,
    RIGHT
};

using AnimVec = vector<shared_ptr<class Texture>>;


class Animator :
    public Component
{
public:

    Animator();

public:
    void Render();
public:
    void Play();
   
    void RegisterTexture(ANIM_STATE _state,class shared_ptr<Texture> _texture);
    void SetMaterial(shared_ptr<class Material> _material);
    void SetMesh(shared_ptr<class Mesh> _material);
    void SetState(ANIM_STATE _state);
    void SetDirection(ANIM_DIRECTION _direction) { mDirection = _direction; }
public:
    
    void PushData(int idx);
    shared_ptr<class Mesh> GetMesh() { return mMesh; }
    ANIM_STATE GetAnimState() { return mCurrentState; }
    ANIM_DIRECTION GetDirState() { return mDirection; }
private:
   
    map<ANIM_STATE,INT8> AnimCounts;
    map<ANIM_STATE, vector<shared_ptr<class Texture>>> mTextureMap;

    ANIM_STATE mCurrentState = ANIM_STATE::IDLE;
    ANIM_DIRECTION mDirection = ANIM_DIRECTION::RIGHT;
    shared_ptr<class Material> mMaterial;
    shared_ptr<class Mesh> mMesh;

    float FrameTime = 0.0f;

};

