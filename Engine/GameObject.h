#pragma once
#include "Object.h"
#include "Component.h"



class GameObject :
    public Object, public enable_shared_from_this<GameObject>
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
    void AddComponent(shared_ptr<class Component> _component);
    void SetParentGameObject(shared_ptr<GameObject> _parent) { mParentObject = _parent; }
    void AddChildObject(shared_ptr<GameObject> _child);
    void SetAlive(bool state) { mAlive = state; }

    

public:
    shared_ptr<Component> GetComponent(COMPONENT_TYPE _type);
    shared_ptr<class Transform> GetTransform();
    shared_ptr<class Collision> GetCollision();
    shared_ptr<class Animator> GetAnimator();
    shared_ptr<class Text> GetText();
    shared_ptr<class GameObject> GetParentObject() { return mParentObject.lock(); };
    shared_ptr<class MonoBehaviour> GetScript();
    vector<shared_ptr<GameObject>> GetChildObjects() { return mChildObejects; }


private: 
    array<shared_ptr<Component>, static_cast<INT32>(COMPONENT_TYPE::END)> mComponentArray;
    vector<shared_ptr<GameObject>> mChildObejects;
    
protected:
    
    weak_ptr<class GameObject> mParentObject;
    bool mAlive = true;

};

