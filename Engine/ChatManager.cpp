#include "pch.h"
#include "ChatManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Animator.h"
#include "Mesh.h"
#include "ResourceManager.h"
#include "ChatScript.h"
#include "Text.h"
#include "SpeachBubbleScript.h"


void ChatManager::Init()
{

	CreateChatObject();


}


void ChatManager::Update()
{
	mChatObject->Update();
	mChatObject->LateUpdate();
}

void ChatManager::LateUpdate()
{
	
}

void ChatManager::Render()
{
	mChatObject->Render();
}

void ChatManager::CreateChatObject()
{

	/////////////////////////////////////////////////////
	//                                                 //
	//				  ChatObject					   //
	//                                                 //
	/////////////////////////////////////////////////////




	//Chat object
	mChatObject = make_shared<GameObject>();


	shared_ptr<Transform> cobTransform = make_shared<Transform>();
	cobTransform->SetScale({ 1.f,1.f,1.f });
	chatScript = make_shared<ChatScript>();
	mChatObject->AddComponent(cobTransform);

	

	mChatObject->AddComponent(chatScript);

	

	//ChatBar BackGround

	shared_ptr<GameObject> ChatBarBackGround = make_shared<GameObject>();

	ChatBarBackGround->SetObjectName(L"ChatBarBackGround");

	shared_ptr<Transform> CBBGTransform = make_shared<Transform>();

	CBBGTransform->SetPosition({ -0.f,-250.0f,1.0f });
	CBBGTransform->SetScale({ 800.f,100.f,1.f });
	CBBGTransform->SetAddRotation({ 0.f,0.f,0.f });
	CBBGTransform->SetMoveType(MOVETYPE::FIX);
	ChatBarBackGround->AddComponent(CBBGTransform);

	shared_ptr<Animator> CBBGAnimator = make_shared<Animator>();

	CBBGAnimator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
	CBBGAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"BackGround"));
	ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CBBGAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Chat\\ChatBar.png");
	CBBGAnimator->SetState(ANIM_STATE::BACKGROUND);

	ChatBarBackGround->AddComponent(CBBGAnimator);

	mChatObject->AddChildObject(ChatBarBackGround);

	ChatBarBackGround->SetAlive(FALSE);


	shared_ptr<GameObject> TexObj = ResourceManager::GetInstance()->CreateText(SENTENCE_MAX,MOVETYPE::FIX);
	TexObj->GetTransform()->SetPosition({ -250.f,-8.f,1.f });


	ChatBarBackGround->AddChildObject(TexObj);
	


	chatScript->SetChatBarBackground(ChatBarBackGround);
	chatScript->AddChatSentenceObject(TexObj);


}



void ChatManager::BroadCastSentence(int idx, string message)
{
	auto chatobj = mChatObjectMap[idx];
	
	chatobj->SetAlive(true);
	shared_ptr<SpeachBubbleScript> script = static_pointer_cast<SpeachBubbleScript>(chatobj->GetScript());
	
	script->SetSentence(message);


}


