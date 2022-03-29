#pragma once

enum class OBJECT_TYPE
{
	GAMEOBJECT,
	COMPONENT,
	SHADER,
	MATERIAL,
	MESH,
	TEXTURE,
	NONE,
	END,

};

enum
{
	OBJECT_TYPE_COUNT = OBJECT_TYPE::END,
	
};

class Object
{
public:
	Object(OBJECT_TYPE _type) { mObjectType = _type; }
public:
	virtual void Init();
	virtual void LateInit();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

public:
	virtual void Load();

public:
	OBJECT_TYPE GetOBJTYPE() { return mObjectType; }
	wstring GetOBJName() { return mObjectName; }

	void SetObjectName(wstring name) { mObjectName = name; }

protected:
	OBJECT_TYPE mObjectType;
	wstring mObjectName;
};

