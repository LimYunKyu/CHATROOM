#include "pch.h"
#include "PlayerScript.h"

#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Timer.h"
#include "Animator.h"


void PlayerScript::Init()
{
}

void PlayerScript::LateInit()
{
}

void PlayerScript::Update()
{

	float DeltaTime = Timer::GetInstance()->GetDeltaTime();
	float MoveData = 0;

	ANIM_STATE IdleState = ANIM_STATE::IDLE;
	ANIM_STATE ComparisonState = ANIM_STATE::IDLE;

	if (InputManager::GetInstance()->GetButton(KEY_TYPE::W))
	{
		
		MoveData = DeltaTime * _speed;
		mGameObject.lock()->GetTransform()->SetAddPosition(XMFLOAT3(0.f, MoveData, 0.f));
		ComparisonState = ANIM_STATE::WALK;
		mGameObject.lock()->GetAnimator()->SetState(ANIM_STATE::WALK);

	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::S))
	{
		MoveData = DeltaTime * _speed;
		mGameObject.lock()->GetTransform()->SetAddPosition(XMFLOAT3(0.f, -MoveData, 0.f));
		ComparisonState = ANIM_STATE::WALK;
		mGameObject.lock()->GetAnimator()->SetState(ANIM_STATE::WALK);

	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::A))
	{
		MoveData = DeltaTime * _speed;
		mGameObject.lock()->GetTransform()->SetAddPosition(XMFLOAT3(-MoveData, 0.f, 0.f));
		ComparisonState = ANIM_STATE::WALK;
		mGameObject.lock()->GetAnimator()->SetState(ANIM_STATE::WALK);
		mGameObject.lock()->GetAnimator()->SetDirection(ANIM_DIRECTION::LEFT);

	}


	if (InputManager::GetInstance()->GetButton(KEY_TYPE::D))
	{
		MoveData = DeltaTime * _speed;
		mGameObject.lock()->GetTransform()->SetAddPosition(XMFLOAT3(MoveData, 0.f, 0.f));
		ComparisonState = ANIM_STATE::WALK;
		mGameObject.lock()->GetAnimator()->SetState(ANIM_STATE::WALK);
		mGameObject.lock()->GetAnimator()->SetDirection(ANIM_DIRECTION::RIGHT);

	}



	if(IdleState == ComparisonState)
		mGameObject.lock()->GetAnimator()->SetState(ANIM_STATE::IDLE);
	

	






}

void PlayerScript::LateUpdate()
{
}

void PlayerScript::Render()
{
}
