#include "pch.h"
#include "UI.h"
#include "GameObject.h"
#include "Transform.h"


UI::UI() : Component(COMPONENT_TYPE::UI)
{



}

void UI::Init()
{
}

void UI::LateInit()
{
}

void UI::Update()
{

	for (auto obj : mUIObjects)
	{
		obj->Update();
	}

}

void UI::LateUpdate()
{
	for (auto obj : mUIObjects)
	{		
		obj->LateUpdate();
	}
}

void UI::Render()
{
	for (auto obj : mUIObjects)
	{
		obj->Render();
	}
}

void UI::AddUIObject(shared_ptr<class GameObject> _object)
{
	mUIObjects.push_back(_object);
	_object->SetParentGameObject(mGameObject.lock());


}


