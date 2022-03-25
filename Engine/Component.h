#pragma once
#include "Object.h"

enum class COMPONENT_TYPE
{
    TRANSFORM,
    COLLISION,
    ANIMATOR,
    CAMARA,
    END,

};


class Component :
    public Object
{
public:
    Component(COMPONENT_TYPE _type);

public:
    COMPONENT_TYPE GetComponentType() { return mComponentType; }

protected:
    COMPONENT_TYPE mComponentType;

};

