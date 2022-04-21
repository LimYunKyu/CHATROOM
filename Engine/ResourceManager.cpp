#include "pch.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Animator.h"
#include "Transform.h"
#include "PlayerScript.h"
#include "Camera.h"
#include "UI.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "Text.h"
#include "ChatScript.h"
#include "CameraScript.h"
#include "ChatManager.h"
#include "ServerTransceiver.h"
#include "SpeachBubbleScript.h"


shared_ptr<Mesh> ResourceManager::LoadRectangleMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Rectangle");
	if (findMesh)
		return findMesh;

	float w2 = 0.5f;
	float h2 = 0.5f;

	vector<Vertex> vec(4);
	vec =
	{
		{ XMFLOAT3(-w2, -h2, 0.f),XMFLOAT2(0.0f,1.0f)},
		{ XMFLOAT3(-w2, +h2, 0.f),XMFLOAT2(0.0f,0.0f)},
		{ XMFLOAT3(+w2, +h2, 0.f),XMFLOAT2(1.0f,0.0f)},
		{ XMFLOAT3(+w2, -h2, 0.f),XMFLOAT2(1.0f,1.0f)},
	};



	vector<UINT32> idx(6);

	// 앞면
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->CreateVertexBuffer(vec);
	mesh->CreateIndexBuffer(idx);
	Add(L"Rectangle", mesh);

	return mesh;
}

void ResourceManager::LoadAnimTextures(shared_ptr<Animator> _animator, ANIM_STATE _state, int count, wstring path)
{


	for (int i = 0; i < count; i++)
	{
		shared_ptr<Texture> CTexture = make_shared<Texture>();
		wstring TPath = path + L"\\" + to_wstring(i) + L".png";
		CTexture->Load(TPath);
		_animator->RegisterTexture(_state, CTexture);

	}

}

void ResourceManager::LoadAnimBackGroundTextures(shared_ptr<class Animator> _animator, ANIM_STATE _state, wstring path)
{
	shared_ptr<Texture> CTexture = make_shared<Texture>();
	CTexture->Load(path);
	_animator->RegisterTexture(_state, CTexture);

}




shared_ptr<class GameObject> ResourceManager::CreatePlayer(int id, SessionRef _session)
{

	



	/////////////////////////////////////////////////////
	//                                                 //
	//				       Player                      //
	//                                                 //
	/////////////////////////////////////////////////////

	//플레이어 생성
	shared_ptr<GameObject> Player = make_shared<GameObject>();
	Player->SetObjectName(L"Player");
	Player->SetServerToId(id);
	Player->SetSession(_session);
	//트랜스폼 컨포넌트
	shared_ptr<Transform> transform = make_shared<Transform>();
	transform->SetPosition({ 50.f, 0.f, 0.f });
	transform->SetScale({ 200.f,200.f,1.f });

	Player->AddComponent(transform);

	//애니메이션

	shared_ptr<Animator> animator = make_shared<Animator>();


	animator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
	animator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Player"));
	ResourceManager::GetInstance()->LoadAnimTextures(animator, ANIM_STATE::IDLE, 17, L"..\\Texture\\Player\\Ranger\\Idle");
	ResourceManager::GetInstance()->LoadAnimTextures(animator, ANIM_STATE::WALK, 7, L"..\\Texture\\Player\\Ranger\\Walk");

	Player->AddComponent(animator);



	//플레이어 움직일 스크립트 등록
	Player->AddComponent(make_shared<PlayerScript>());

	//플레이어 서버 송수신기
	Player->AddComponent(make_shared<ServerTransceiver>());



	/////////////////////////////////////////////////////
	//                                                 //
	//				       Camera                      //
	//                                                 //
	/////////////////////////////////////////////////////



	//플레이어 따라다닐 카메라 생성


	shared_ptr<GameObject> cameraobj = make_shared<GameObject>();


	//카메라 트랜스폼..
	cameraobj->SetObjectName(L"PlayerCamera");
	shared_ptr<Transform> cameratransform = make_shared<Transform>();
	cameratransform->SetPosition({ 0,0.0f,-1.0f });
	cameratransform->SetScale({ 1.f,1.f,1.0f });
	cameratransform->SetAddRotation({ 0.f,0.f,0.f });
	cameraobj->AddComponent(cameratransform);


	//카메라 컴포넌트
	shared_ptr<Camera> camera = make_shared<Camera>();
	camera->SetMapSize(1344.f, 840.f);
	cameraobj->AddComponent(camera);

	//카메라 자식 오브젝트로 추가

	Player->AddChildObject(cameraobj);
	
	

	/////////////////////////////////////////////////////
	//                                                 //
	//				       UI                          //
	//                                                 //
	/////////////////////////////////////////////////////


	//UI오브젝트생성
	shared_ptr<GameObject> UIObject = make_shared<GameObject>();


	//UI트랜스폼 생성
	shared_ptr<Transform>  UITransform = make_shared<Transform>();
	UITransform->SetPosition({ 0.0f, 0.0f, 0.0f });
	UIObject->AddComponent(UITransform);

	//UI컴포넌트 생성
	shared_ptr<UI> CUI = make_shared<UI>();
	UIObject->AddComponent(CUI);


	Player->AddChildObject(UIObject);

	
	/////////////////////////////////////////////////////
	//                                                 //
	//				UI/NameBar/NoBackGround            //
	//                                                 //
	/////////////////////////////////////////////////////


	//NameBar생성

	shared_ptr<GameObject> NameBar = make_shared<GameObject>();

	NameBar->SetObjectName(L"PlayerNameBar");

	//namebar 트랜스폼생성
	shared_ptr<Transform> namebartransform = make_shared<Transform>();
	namebartransform->SetPosition({ -50.f,100.0f,5.0f });
	namebartransform->SetScale({ 1.f,1.f,1.f });
	namebartransform->SetAddRotation({ 0.f,0.f,0.f });
	NameBar->AddComponent(namebartransform);

	//namebar 애니메이터 생성

	shared_ptr<Animator> NameAnimator = make_shared<Animator>();
	int SentenceLength = 30;

	//매쉬 생성
	shared_ptr<Mesh> NameMesh = make_shared<Mesh>();

	NameAnimator->SetMesh(NameMesh);
	NameAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Text"));
	NameAnimator->SetState(ANIM_STATE::BACKGROUND);
	ResourceManager::GetInstance()->LoadAnimBackGroundTextures(NameAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Font\\font.dds");
	NameBar->AddComponent(NameAnimator);
	
	//Text 생성
	shared_ptr<Text> NameText = make_shared<Text>(NAMELENGTH);

	NameBar->AddComponent(NameText);

	NameText->InitFontData(fonttypevec);

	const char* name;
	name =  "ME\0";
	
	NameText->SetSentence(name);

	UIObject->AddChildObject(NameBar);
	


	//speach bubble
	shared_ptr<GameObject> speachbubble = CreateSpeachBubble(id);

	UIObject->AddChildObject(speachbubble);
	






	return Player;
}

shared_ptr<class GameObject> ResourceManager::CreateText(int _textlen, MOVETYPE _type)
{
	/////////////////////////////////////////////////////
	//                                                 //
	//				 UI/ChatBarSentence                //
	//                                                 //
	/////////////////////////////////////////////////////


	//Sentence생성

	shared_ptr<GameObject> ChatBarSentence = make_shared<GameObject>();

	ChatBarSentence->SetObjectName(L"Sentence");

	//ChatbarSentence 트랜스폼생성
	shared_ptr<Transform> CBSTransform = make_shared<Transform>();
	CBSTransform->SetPosition({ -0.f,-0.f,0.0f });
	CBSTransform->SetScale({ 1.f,1.f,1.f });
	CBSTransform->SetAddRotation({ 0.f,0.f,0.f });
	CBSTransform->SetMoveType(_type);
	
	ChatBarSentence->AddComponent(CBSTransform);

	//애니메이터 생성

	shared_ptr<Animator> CBSAnimator = make_shared<Animator>();
	

	//매쉬 생성
	shared_ptr<Mesh> CBSMesh = make_shared<Mesh>();

	CBSAnimator->SetMesh(CBSMesh);
	CBSAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Text"));
	CBSAnimator->SetState(ANIM_STATE::BACKGROUND);
	ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CBSAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Font\\font.dds");
	ChatBarSentence->AddComponent(CBSAnimator);

	//Text 생성
	shared_ptr<Text> text = make_shared<Text>(_textlen);

	ChatBarSentence->AddComponent(text);

	text->InitFontData(fonttypevec);

	return ChatBarSentence;


}

shared_ptr<class GameObject> ResourceManager::CreateSpeachBubble(int id)
{

	/////////////////////////////////////////////////////
	//                                                 //
	//				 UI/SpeachBubble                   //
	//                                                 //
	/////////////////////////////////////////////////////


	shared_ptr<GameObject> SpeachBubbleObj = make_shared<GameObject>();

	ChatManager::GetInstance()->RegisterSpeachBubble(id, SpeachBubbleObj);
	SpeachBubbleObj->SetAlive(false);
	shared_ptr<Transform> SBOTransform = make_shared<Transform>();
	SBOTransform->SetScale({ 1.f,1.f,1.f });

	SpeachBubbleObj->AddComponent(SBOTransform);

	
	//ChatBar BackGround

	shared_ptr<GameObject> SpeachBubbleBackGround = make_shared<GameObject>();

	SpeachBubbleBackGround->SetObjectName(L"SpeachBubbleBackGround");

	shared_ptr<Transform> CBBGTransform = make_shared<Transform>();

	CBBGTransform->SetPosition({ -0.f,150.0f,1.0f });
	CBBGTransform->SetScale({ 200.f,200.f,1.f });
	CBBGTransform->SetAddRotation({ 0.f,0.f,0.f });
	
	SpeachBubbleBackGround->AddComponent(CBBGTransform);

	shared_ptr<Animator> CBBGAnimator = make_shared<Animator>();

	CBBGAnimator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
	CBBGAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"BackGround"));
	ResourceManager::GetInstance()->LoadAnimBackGroundTextures(CBBGAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Chat\\BlueSpeechBubble.png");
	CBBGAnimator->SetState(ANIM_STATE::BACKGROUND);


	SpeachBubbleBackGround->AddComponent(CBBGAnimator);

	SpeachBubbleObj->AddChildObject(SpeachBubbleBackGround);

	//SpeachBubbleBackGround->SetAlive(false);


	shared_ptr<GameObject> TexObj1 = ResourceManager::GetInstance()->CreateText(SPEACHSENTENCE_MAX,MOVETYPE::MOVE);
	TexObj1->GetTransform()->SetPosition({ -70.f, 15.f,1.f });
	//TexObj1->SetAlive(false);

	shared_ptr<GameObject> TexObj2 = ResourceManager::GetInstance()->CreateText(SPEACHSENTENCE_MAX, MOVETYPE::MOVE);
	TexObj2->GetTransform()->SetPosition({ -70.f,-5.f,1.f });
	//TexObj1->SetAlive(true);

	SpeachBubbleBackGround->AddChildObject(TexObj1);
	SpeachBubbleBackGround->AddChildObject(TexObj2);

	shared_ptr<SpeachBubbleScript> SBScript = make_shared<SpeachBubbleScript>();
	SBScript->AddSentenceObj(TexObj1);
	SBScript->AddSentenceObj(TexObj2);
	SBScript->SetBackGround(SpeachBubbleBackGround);
	SpeachBubbleObj->AddComponent(SBScript);


	return SpeachBubbleObj;
}

shared_ptr<class GameObject> ResourceManager::CreateOtherPlayer(int id)
{
	/////////////////////////////////////////////////////
	//                                                 //
	//				       Player                      //
	//                                                 //
	/////////////////////////////////////////////////////

	

	//플레이어 생성
	shared_ptr<GameObject> Player = make_shared<GameObject>();
	Player->SetObjectName(L"OtherPlayer");
	Player->SetServerToId(id);
	//트랜스폼 컨포넌트
	shared_ptr<Transform> transform = make_shared<Transform>();
	transform->SetPosition({ 50.f, 0.f, 0.f });
	transform->SetScale({ 200.f,200.f,1.f });

	Player->AddComponent(transform);

	//애니메이션

	shared_ptr<Animator> animator = make_shared<Animator>();


	animator->SetMesh(ResourceManager::GetInstance()->LoadRectangleMesh());
	animator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Player"));
	ResourceManager::GetInstance()->LoadAnimTextures(animator, ANIM_STATE::IDLE, 17, L"..\\Texture\\Player\\Ranger\\Idle");
	ResourceManager::GetInstance()->LoadAnimTextures(animator, ANIM_STATE::WALK, 7, L"..\\Texture\\Player\\Ranger\\Walk");

	Player->AddComponent(animator);



	/////////////////////////////////////////////////////
	//                                                 //
	//				       UI                          //
	//                                                 //
	/////////////////////////////////////////////////////


	//UI오브젝트생성
	shared_ptr<GameObject> UIObject = make_shared<GameObject>();


	//UI트랜스폼 생성
	shared_ptr<Transform>  UITransform = make_shared<Transform>();
	UITransform->SetPosition({ 0.0f, 0.0f, 0.0f });
	UIObject->AddComponent(UITransform);

	//UI컴포넌트 생성
	shared_ptr<UI> CUI = make_shared<UI>();
	UIObject->AddComponent(CUI);


	Player->AddChildObject(UIObject);


	/////////////////////////////////////////////////////
	//                                                 //
	//				UI/NameBar/NoBackGround            //
	//                                                 //
	/////////////////////////////////////////////////////


	//NameBar생성

	shared_ptr<GameObject> NameBar = make_shared<GameObject>();

	NameBar->SetObjectName(L"OtherPlayerNameBar");

	//namebar 트랜스폼생성
	shared_ptr<Transform> namebartransform = make_shared<Transform>();
	namebartransform->SetPosition({ -50.f,100.0f,5.0f });
	namebartransform->SetScale({ 1.f,1.f,1.f });
	namebartransform->SetAddRotation({ 0.f,0.f,0.f });
	NameBar->AddComponent(namebartransform);

	//namebar 애니메이터 생성

	shared_ptr<Animator> NameAnimator = make_shared<Animator>();
	int SentenceLength = 30;

	//매쉬 생성
	shared_ptr<Mesh> NameMesh = make_shared<Mesh>();

	NameAnimator->SetMesh(NameMesh);
	NameAnimator->SetMaterial(ResourceManager::GetInstance()->Get<Material>(L"Text"));
	NameAnimator->SetState(ANIM_STATE::BACKGROUND);
	ResourceManager::GetInstance()->LoadAnimBackGroundTextures(NameAnimator, ANIM_STATE::BACKGROUND, L"..\\Texture\\Font\\font.dds");
	NameBar->AddComponent(NameAnimator);

	//Text 생성
	shared_ptr<Text> NameText = make_shared<Text>(NAMELENGTH);

	NameBar->AddComponent(NameText);

	NameText->InitFontData(fonttypevec);

	const char* name;
	name = "OTHER\0";

	NameText->SetSentence(name);

	UIObject->AddChildObject(NameBar);



	//speach bubble
	shared_ptr<GameObject> speachbubble = CreateSpeachBubble(id);

	UIObject->AddChildObject(speachbubble);
	

	return Player;
}

void ResourceManager::Init()
{
	LoadFontDataFromFile("../Texture/Font/fontdata.txt");
	CreateDefaultShader();
	CreateDefaultMaterial();
}

void ResourceManager::CreateDefaultShader()
{
	//Default Shader

	{


		shared_ptr<Shader> shader = make_shared<Shader>();
		shader->CreateShader(L"..\\Shader\\Default.fx");
		Add<Shader>(L"Default", shader);

	}

	//Text Shader

	{


		shared_ptr<Shader> shader = make_shared<Shader>();
		shader->CreateShader(L"..\\Shader\\Text.fx");
		Add<Shader>(L"Text", shader);

	}

}

void ResourceManager::CreateDefaultMaterial()
{
	// Default
	{
		shared_ptr<Shader> shader = Get<Shader>(L"Default");
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		Add<Material>(L"Player", material);
	}


	// BackGround
	{
		shared_ptr<Shader> shader = Get<Shader>(L"Default");
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		Add<Material>(L"BackGround", material);
	}

	// Text
	{
		shared_ptr<Shader> shader = Get<Shader>(L"Text");
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		Add<Material>(L"Text", material);
	}

}

void ResourceManager::LoadTextures(const wstring& path, shared_ptr<Material> material, int count)
{

	for (int i = 0; i < count; i++)
	{
		shared_ptr<Texture> CTexture = make_shared<Texture>();
		wstring TPath = path + L"\\" + to_wstring(i) + L".png";
		CTexture->Load(TPath);


	}



}



bool ResourceManager::LoadFontDataFromFile(const char* fontFilename)
{

	fonttypevec = make_shared<vector<FontType>>();

	ifstream fin;
	int i;
	char temp;

	FontType fonttype;

	

	// Read in the font size and spacing between chars.
	fin.open(fontFilename);
	if (fin.fail())
	{
		return false;
	}

	// Read in the 95 used ascii characters for text.
	for (i = 0; i < 95; i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}

		fin >> fonttype.left;
		fin >> fonttype.right;
		fin >> fonttype.size;

		fonttypevec->push_back(fonttype);
		
	}

	// Close the file.
	fin.close();

	return true;
}

