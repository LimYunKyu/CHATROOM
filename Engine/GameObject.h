#pragma once
#include "Object.h"
#include "Component.h"

class GameObject :
    public Object
{
public:
    GameObject();

public:
    void Init();
    void LateInit();
    void Update();
    void LateUpdate();
    void Render();

public:
    void SetComponent(shared_ptr<class Component> _component);

public:
    shared_ptr<Component> GetComponent(COMPONENT_TYPE _type);

private:
    array<shared_ptr<Component>, static_cast<INT32>(COMPONENT_TYPE::END)> mComponentArray;


};

