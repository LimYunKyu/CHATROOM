#pragma once
class Engine
{
public:
	Engine();
	~Engine();
public:
	bool Initialize(WindowInfo& winfo);
	bool Update();
	bool Render();

public:
	bool ScreenResize();
	const WindowInfo GetWinfo() { return mWinfo; }
	shared_ptr<class GraphcisProcessor> GetGraphicsProcessor() { return mGraphicsProcessor; }

	void CreateFontBuffer(shared_ptr<class Mesh> _mesh, int FontLength);
	bool UpdateSentence(shared_ptr<class Mesh>, const char* text, int positionX, int positionY);
	void BuildVertexArray(void*, const char*, float, float);


private:
	WindowInfo Garbage = {};
	WindowInfo& mWinfo = Garbage;

	shared_ptr<class GraphcisProcessor> mGraphicsProcessor;

	shared_ptr<class GameObject> mPlayer;
	shared_ptr<class GameObject> mBackGround;
	shared_ptr<class GameObject> mCamera;
	shared_ptr<class GameObject> mFont;

	
private:
	//Test

	bool LoadFontDataFromFile(const char* fontFilename, const WCHAR* textureFilename);
	bool LoadFontData(const char* filename);

	FontType*  mFontType;
	shared_ptr<class Texture> mFontTextre;

};

