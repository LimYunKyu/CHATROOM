#include "pch.h"
#include "Animator.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "Timer.h"
#include "Texture.h"
#include "Engine.h"
#include "GraphcisProcessor.h"
#include "BufferManager.h"


Animator::Animator() : Component(COMPONENT_TYPE::ANIMATOR)
{
}

void Animator::Render()
{
	Play();
	mMaterial->Render();
	mMesh->Render();

}

void Animator::Play()
{

	int idx = static_cast<int>(FrameTime);


	FrameTime += (Timer::GetInstance()->GetDeltaTime()) * 10.f;

	if (FrameTime >= AnimCounts[mCurrentState])
		FrameTime = 0.0f;

	
	PushData(idx);
	MaterialParams materialData;

	if ((mCurrentState == ANIM_STATE::FONT))
		return;

	//¿ÞÂÊ0, ¿À¸¥ÂÊ 1
	if(mDirection == ANIM_DIRECTION::LEFT)
		materialData.SetTexOn(0, 0);
	if (mDirection == ANIM_DIRECTION::RIGHT)
		materialData.SetTexOn(0, 1);

	BufferManager::GetInstance()->GetConstantBuffer(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&materialData);

}



void Animator::RegisterTexture(ANIM_STATE _state, shared_ptr<Texture> _texture)
{
	mTextureMap[_state].push_back(_texture);
	AnimCounts[_state] = mTextureMap[_state].size();


}

void Animator::SetMaterial(shared_ptr<class Material> _material)
{
	mMaterial = _material;
}

void Animator::SetMesh(shared_ptr<class Mesh> _material)
{
	mMesh = _material;
}

void Animator::SetState(ANIM_STATE _state)
{
	if (mCurrentState != _state)
		FrameTime = 0.0f;

	mCurrentState = _state;


}

void Animator::PushData(int idx)
{
	if (mTextureMap[mCurrentState][idx])
	{
		SRV_REGISTER reg = SRV_REGISTER(static_cast<INT8>(SRV_REGISTER::t0));
		ID3D11ShaderResourceView* srv = mTextureMap[mCurrentState][idx]->GetSRV();

		GEngine->GetGraphicsProcessor()->GetDeviceContext()->PSSetShaderResources(0, 1, &srv);
	}


}

