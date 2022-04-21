#pragma once
enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
	RETURN = VK_RETURN,
};

enum class KEY_STATE
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<INT32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<INT32>(KEY_STATE::END),
};

class InputManager
{

	DECLARE_SINGLE(InputManager)
public:
	void Init(HWND hwnd);
	void Update();
public:
	// 누르고 있을 때
	bool GetButton(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESS; }
	// 맨 처음 눌렀을 때
	bool GetButtonDown(KEY_TYPE key) { return GetState(key) == KEY_STATE::DOWN; }
	// 맨 처음 눌렀다 뗐을 때
	bool GetButtonUp(KEY_TYPE key) { return GetState(key) == KEY_STATE::UP; }

	bool GetButton(INT32 key) { return GetState(key) == KEY_STATE::PRESS; }

	bool GetButtonDown(INT32 key) { return GetState(key) == KEY_STATE::DOWN; }

	const POINT& GetMousePos() { return _mousePos; }

	char* GetSentnece() { return sentence; }

	void ReceiveText(TCHAR text);

	void ResetSentence();

	void SetChatOnState(bool state) { _ChatOn = state; }

	bool GetChatSate() { return _ChatOn; }
	
private:
	inline KEY_STATE GetState(KEY_TYPE key) { return _states[static_cast<UINT8>(key)]; }
	inline KEY_STATE GetState(INT32 key) { return _states[key]; }
private:
	vector<KEY_STATE> _states;
	POINT _mousePos = {};
	HWND _hwnd;
	bool _ChatOn = false;
	TCHAR str[256];
	char sentence[SENTENCE_MAX];


};
