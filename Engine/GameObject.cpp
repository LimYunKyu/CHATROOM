#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{
}

void GameObject::Init()
{
}

void GameObject::LateInit()
{
}

void GameObject::Update()
{
}

void GameObject::LateUpdate()
{
}

void GameObject::Render()
{
}

void GameObject::SetComponent(shared_ptr<class Component> _component)
{
	INT32 idx = static_cast<INT32>(_component->GetComponentType());
	
	mComponentArray[idx] = _component;

}

shared_ptr<Component> GameObject::GetComponent(COMPONENT_TYPE _type)
{
	INT32 idx = static_cast<INT32>(_type);

	return mComponentArray[idx];
}
