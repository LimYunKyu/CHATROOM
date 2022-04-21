#pragma once
#include "Component.h"


class UI :
    public Component
{
public:
    UI();
public:
    void Init();
    void LateInit();
    void Update();
    void LateUpdate();
    void Render();

public:
    void AddUIObject(shared_ptr<class GameObject> _object);
    

private:
    vector<shared_ptr<class GameObject>> mUIObjects;

    
};

