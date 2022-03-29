#pragma once
#include "Component.h"


enum class ANIM_STATE
{
    IDLE,
    IDLE2,
    WALK,
    BACKGROUND,

};

enum class ANIM_DIRECTION
{

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
    
    void PushData(int idx);

private:
   
    map<ANIM_STATE,INT8> AnimCounts;
    map<ANIM_STATE, vector<shared_ptr<class Texture>>> mTextureMap;

    ANIM_STATE mCurrentState = ANIM_STATE::IDLE;
    ANIM_DIRECTION mDirection = ANIM_DIRECTION::RIGHT;
    shared_ptr<class Material> mMaterial;
    shared_ptr<class Mesh> mMesh;

    float FrameTime = 0.0f;

};

