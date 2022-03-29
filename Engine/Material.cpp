#include "pch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "Timer.h"

Material::Material() : Object(OBJECT_TYPE::MATERIAL)
{
}

void Material::SetShader(shared_ptr<class Shader> shader)
{
	mShader = shader;
}



void Material::Update()
{
	if (mShader.get())
		mShader->Update();
}

void Material::LateUpdate()
{
	if (mShader.get())
		mShader->LateUpdate();
}

void Material::Render()
{
	if (mShader.get())
	{
		mShader->Render();
	}

	

}
