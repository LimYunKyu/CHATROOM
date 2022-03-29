#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Collision.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{


}

void GameObject::Init()
{
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->Init();
	}

}

void GameObject::LateInit()
{
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->LateInit();
	}
}

void GameObject::Update()
{
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->LateUpdate();
	}
}

void GameObject::Render()
{
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->Render();
	}
}

void GameObject::AddComponent(shared_ptr<class Component> _component)
{
	INT32 idx = static_cast<INT32>(_component->GetComponentType());
	
	mComponentArray[idx] = _component;
	_component->SetGameObject(shared_from_this());

}

shared_ptr<Component> GameObject::GetComponent(COMPONENT_TYPE _type)
{
	INT32 idx = static_cast<INT32>(_type);

	return mComponentArray[idx];
}

shared_ptr<class Transform> GameObject::GetTransform()
{
	INT32 idx = static_cast<INT32>(COMPONENT_TYPE::TRANSFORM);


	return static_pointer_cast<Transform>(mComponentArray[idx]);
}

shared_ptr<class Collision> GameObject::GetCollision()
{
	INT32 idx = static_cast<INT32>(COMPONENT_TYPE::COLLISION);
	return static_pointer_cast<Collision>(mComponentArray[idx]);
}

shared_ptr<class Animator> GameObject::GetAnimator()
{
	INT32 idx = static_cast<INT32>(COMPONENT_TYPE::ANIMATOR);
	return static_pointer_cast<Animator>(mComponentArray[idx]);
}
