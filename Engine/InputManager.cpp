#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND hwnd)
{
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
	_hwnd = hwnd;
}

void InputManager::Update()
{

	
	HWND hwnd = ::GetActiveWindow();
	if (hwnd != _hwnd)
	{
		for (UINT key = 0; key < KEY_TYPE_COUNT; key++)
			_states[key] = KEY_STATE::NONE;

		return;

	}

	BYTE asciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(asciiKeys) == false)
		return;

	for (UINT32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		// Ű�� ���� ������ true
		if (asciiKeys[key] & 0x80)
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::PRESS;
			else
				state = KEY_STATE::DOWN;
		}
		else
		{
			KEY_STATE& state = _states[key];

			// ���� �����ӿ� Ű�� ���� ���¶�� UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
				state = KEY_STATE::UP;
			else
				state = KEY_STATE::NONE;
		}
	}


}

void InputManager::ReceiveText(TCHAR text)
{
	int len = 0;

	if (_ChatOn)
	{
		if (text == '\r')
		{

			return;
		}//����
			

		len = lstrlen(str);

		if (len > (SENTENCE_MAX))
			return;


		if (text == '\b') //back space
		{
			if (len > 0) //���� ���ڰ� 0���� �ƴϸ� 
			{
				str[len - 1] = 0;
				len -= 1;
				
			}
			
		}
		else
		{
			if (len >= (SENTENCE_MAX))
				return;


			str[len] = text;
			str[len + 1] = 0;


		}
		WideCharToMultiByte(CP_ACP, 0, str, SENTENCE_MAX, sentence, SENTENCE_MAX, NULL, NULL);
	}
	
}

void InputManager::ResetSentence()
{
	str[0] = 0;
	ZeroMemory(sentence, SENTENCE_MAX);


}
