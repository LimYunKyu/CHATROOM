#pragma once
#include "MonoBehaviour.h"
class CameraScript :
    public MonoBehaviour
{
public:
	CameraScript();
	virtual ~CameraScript();

	virtual void LateUpdate() override;

private:
	float		_speed = 100.f;
};

