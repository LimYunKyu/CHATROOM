#pragma once
#include "Component.h"



enum class MOVETYPE
{
    FIX,
    MOVE,

};

class Transform :
    public Component
{
public:
    Transform();


public:
    void Update();
    void LateUpdate();
    void Render();
public:
    const XMFLOAT3 GetPosition() { return mPos; }
    const XMFLOAT3 GetWorldPosition() { return mWorldPos; }
    const XMFLOAT3 GetScale() { return mScale; }
    const XMFLOAT3 GetRotation() { return mRotation; }
    const XMMATRIX GetTransMatrix() { return mTransMatrix; }
    const XMMATRIX GetScaleMatrix() { return mScaleMatrix; }
    const XMMATRIX GetRotationMatrix() { return mRotationMatrix; }
    const XMMATRIX GetWorldMatrix() { return mWorldMatrix; }

public:
    void SetPosition(XMFLOAT3 _pos); 
    void SetScale(XMFLOAT3 _scale);
    void SeRotation(XMFLOAT3 _rotation);
    
    void SetAddPosition(XMFLOAT3 _pos); 
    void SetAddScale(XMFLOAT3 _scale); 
    void SetAddRotation(XMFLOAT3 _rotation);
    void SetParentPos(XMFLOAT3 _parentpos);
    void SetWorldPos(XMFLOAT3 _worldpos);
    void SetMoveType(MOVETYPE type) { mMoveType = type; }

public:
    void PushData();
  

private:
    XMFLOAT3 mWorldPos;
    XMFLOAT3 mParentPos;
    XMFLOAT3 mPos;
    XMFLOAT3 mScale;
    XMFLOAT3 mRotation;

    XMMATRIX mTransMatrix;
    XMMATRIX mScaleMatrix;
    XMMATRIX mRotationMatrix;

    XMMATRIX mWorldMatrix;

    MOVETYPE mMoveType = MOVETYPE::MOVE;

};

