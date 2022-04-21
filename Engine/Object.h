#pragma once

enum class OBJECT_TYPE
{
	GAMEOBJECT,
	COMPONENT,
	SHADER,
	MATERIAL,
	MESH,
	TEXTURE,
	SCENE,
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

	void SetObjectName(wstring name) { mObjectName = name; }
	void SetServerToId(uint32 id) { ServerToId = id; }
	void SetSession(shared_ptr<class Session> _session) { session = _session; }


public:


	OBJECT_TYPE GetOBJTYPE() { return mObjectType; }
	wstring GetOBJName() { return mObjectName; }
	uint32 GetServerToId() { return ServerToId; }
	shared_ptr<class Session> GetSession() { return session; }
protected:
	OBJECT_TYPE mObjectType;
	wstring mObjectName;
	uint32 ServerToId = 0;
	shared_ptr<class Session> session;
};

