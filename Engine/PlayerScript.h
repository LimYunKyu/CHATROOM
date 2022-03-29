#pragma once
#include "MonoBehaviour.h"
class PlayerScript :
    public MonoBehaviour
{
public:
    void Init();
    void LateInit();
    void Update();
    void LateUpdate();
    void Render();
private:
    float		_speed = 100.f;

};

