#pragma once
#include "Object.h"

enum
{
	//MATERIAL_INT_COUNT = 4,
	//MATERIAL_FLOAT_COUNT = 4,
	MATERIAL_TEXTURE_COUNT = 4,
	
};


struct MaterialParams
{
	//array<UINT32, MATERIAL_INT_COUNT> intParams;
	//array<float, MATERIAL_FLOAT_COUNT> floatParams;
	array<UINT32, MATERIAL_TEXTURE_COUNT> texOnParams;
	

	//void SetInt(UINT8 index, UINT32 value) { intParams[index] = value; }
	//void SetFloat(UINT8 index, float value) { floatParams[index] = value; }
	void SetTexOn(UINT8 index, UINT32 value) { texOnParams[index] = value; }
	

};

class Material :
    public Object
{
public:
    Material();
public:
	void SetShader(shared_ptr<class Shader> shader);
	
public:
	void Update();
	void LateUpdate();
	void Render();
private:
    shared_ptr<class Shader>   mShader;
  

	float FrameTime = 0.0f;
};

