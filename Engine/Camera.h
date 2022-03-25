#pragma once
#include "Component.h"


enum class PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC,

};


class Camera :
    public Component
{

public:
    Camera();
};

