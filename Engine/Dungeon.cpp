#include "pch.h"
#include "Dungeon.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "PlayerScript.h"
#include "UI.h"
#include "ChatScript.h"
#include "SceneManager.h"
#include "GameObjectCollector.h"

Dungeon::Dungeon()
{
	Init();
	LateInit();
}

void Dungeon::Init()
{


#pragma region BackGround

	{
		mBackGround = make_shared<GameObject>();
		mBackGround->SetObjectName(L"BackGroubd");

		shared_ptr<Transform> CTransform = make_shared<Transform>();
		CTransform->SetPosition({ 0.0f,0.0f,10.f });
		CTransform->SetScale({ 1344.f,840.0f,1.0f });
		CTransform->SetAddRotation({ 0.f,0.f,0.f });
		mBackGround->AddComponent(CTransform);

		shared_ptr<Animator> CAnimator = make_shared<Animator>();


		CAnimator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
		CAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"BackGround"));
		ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\BackGround\\BackGround1.png");
		CAnimator->SetState(ANIM_STATE::BACKGROUND);

		mBackGround->AddComponent(CAnimator);

		SceneManager::GetInstance()->SetMapSize({ 1344.f, 840.f });

	}




#pragma endregion


	


}

void Dungeon::LateInit()
{
}

void Dungeon::Update()
{

	mBackGround->Update();
	GameObjectCollector::GetInstance()->Update();
	
	


}

void Dungeon::LateUpdate()
{
	mBackGround->LateUpdate();
	GameObjectCollector::GetInstance()->LateUpdate();
	
	
}

void Dungeon::Render()
{

	if (mBackGround.get() == nullptr)
		int a = 5;
	mBackGround->Render();
	GameObjectCollector::GetInstance()->Render();
	
	
}
