#pragma once
#include "Component.h"

using FontTypeVec = vector<shared_ptr<FontType>>;


class Text :
	public Component
{
public:
	Text(INT32 _maxlength);
	~Text();
	
public:
	void InitFontData(shared_ptr<vector<FontType>> _fonttype);
	void SetSentence(const char* _sentnece);
	void SetLength(INT32 _length) { mLength = _length; }
	const char* GetSentence() { return mSentence; }

private:
	void CreateFontBuffer();
	bool UpdateSentence();
	void BuildVertexArray(void* vertices, const char* sentence, float drawX, float drawY);

private:

	shared_ptr<vector<FontType>> mFontType;
	vector<shared_ptr<FontType>> test;
	
	USE_LOCK

	INT32 mLength = 0;
	INT32 mMaxLength = 0;
	const char* mSentence;
};

