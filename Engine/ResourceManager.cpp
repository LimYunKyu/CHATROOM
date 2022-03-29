#include "pch.h"
#include "ResourceManager.h"
#include "Material.h"
#include "Animator.h"

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

	// ¾Õ¸é
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




void ResourceManager::Init()
{
	CreateDefaultShader();
	CreateDefaultMaterial();
}

void ResourceManager::CreateDefaultShader()
{
	//Default Shader

	{


		shared_ptr<Shader> shader = make_shared<Shader>();
		shader->CreateShader(L"..\\Shader\\Tutorial.fx");
		Add<Shader>(L"Default", shader);

	}

	

}

void ResourceManager::CreateDefaultMaterial()
{
	// Default
	{
		shared_ptr<Shader> shader = Get<Shader>(L"Default");
		shared_ptr<Mesh> mesh = Get<Mesh>(L"Rectangle");		
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		Add<Material>(L"Player", material);
	}


	// BackGround
	{
		shared_ptr<Shader> shader = Get<Shader>(L"Default");
		shared_ptr<Mesh> mesh = Get<Mesh>(L"Rectangle");		
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		Add<Material>(L"BackGround", material);
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

