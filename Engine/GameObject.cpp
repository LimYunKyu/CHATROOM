#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Animator.h"
#include "Collision.h"
#include "Text.h"
#include "MonoBehaviour.h"
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

	for (auto obj : mChildObejects)
	{
		if (mAlive)
		{
			obj->Init();
		}
		
	}

}

void GameObject::LateInit()
{


	if (!mAlive)
		return;
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->LateInit();
	}

	for (auto obj : mChildObejects)
	{
		if (mAlive)
		{
			obj->LateInit();
		}
	}



}

void GameObject::Update()
{
	
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->Update();
	}
	
	for (auto obj : mChildObejects)
	{
		if (mAlive)
		{
			obj->Update();

		}
	}
}

void GameObject::LateUpdate()
{

	if (!mAlive)
		return;
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->LateUpdate();
	}

	for (auto obj : mChildObejects)
	{
		if (mAlive)
		{
			obj->LateUpdate();

		}
	}
}

void GameObject::Render()
{

	if (!mAlive)
		return;
	for (auto component : mComponentArray)
	{
		if (component.get())
			component->Render();
	}

	for (auto obj : mChildObejects)
	{
		if (mAlive)
		{
			obj->Render();

		}
	}
}

void GameObject::AddComponent(shared_ptr<class Component> _component)
{
	INT32 idx = static_cast<INT32>(_component->GetComponentType());

	mComponentArray[idx] = _component;
	_component->SetGameObject(shared_from_this());

}

void GameObject::AddChildObject(shared_ptr<GameObject> _child)
{

	mChildObejects.push_back(_child);
	_child->SetParentGameObject(shared_from_this());
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

shared_ptr<class Text> GameObject::GetText()
{
	INT32 idx = static_cast<INT32>(COMPONENT_TYPE::TEXT);
	return static_pointer_cast<Text>(mComponentArray[idx]);
}

shared_ptr<class MonoBehaviour> GameObject::GetScript()
{
	INT32 idx = static_cast<INT32>(COMPONENT_TYPE::MONOBEHAVIOUR);
	return static_pointer_cast<MonoBehaviour>(mComponentArray[idx]);
}
