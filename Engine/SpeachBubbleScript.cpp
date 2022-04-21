#include "pch.h"
#include "SpeachBubbleScript.h"
#include "Timer.h"
#include "ChatManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Text.h"


void SpeachBubbleScript::SetSentence(string sentence)
{
	 mCurrentSentence = sentence; 
	 mStartTime = 0.0f;
	 mAlive = true;
	 mBackGround->SetAlive(true);
	 for (auto sentence : mSenctenceVec)
	 {
		 sentence->SetAlive(true);
	 }

}

void SpeachBubbleScript::LateUpdate()
{

	if (!mAlive)
		return;

	if (mStartTime < mAliveTime)
	{
		mStartTime += Timer::GetInstance()->GetDeltaTime();
		
		char sentence[SENTENCE_MAX]; 
		strcpy(sentence, mCurrentSentence.c_str());
		
		int len = strlen(sentence);

		char sentence1[SPEACHSENTENCE_MAX+1] = " ";
		char sentence2[SPEACHSENTENCE_MAX+1] = " ";

		if (len > SENTENCE_MAX)
		{
			strcpy(sentence1, sentence);
			sentence1[40] = 0;

			strcpy(sentence2, &sentence[40]);
			sentence2[40] = 0;

		}
		else
		{

			strcpy(sentence1, sentence);

		}



		
		mSenctenceVec[0]->GetText()->SetSentence(sentence1);
		mSenctenceVec[1]->GetText()->SetSentence(sentence2);
		

		
		
	}
	else
	{
		mAlive = false;
		mBackGround->SetAlive(false);
		for (auto sentence : mSenctenceVec)
		{
			sentence->SetAlive(false);
		}
		mStartTime = 0;
		mGameObject.lock()->SetAlive(false);
	}



}
