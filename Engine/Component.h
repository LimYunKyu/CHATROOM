#pragma once
#include "Object.h"

enum class COMPONENT_TYPE
{
   
    TRANSFORM,
    COLLISION,
    UI,
    CAMARA,
    ANIMATOR,
    MONOBEHAVIOUR,
    END,

};


class Component :
    public Object
{
public:
    Component(COMPONENT_TYPE _type);

public:
    COMPONENT_TYPE GetComponentType() { return mComponentType; }
public:
    void SetGameObject(shared_ptr<class GameObject> object) { mGameObject = object; }
    
protected:
    COMPONENT_TYPE mComponentType;
    weak_ptr<class GameObject> mGameObject;

};

