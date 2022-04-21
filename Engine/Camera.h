#pragma once
#include "Component.h"


enum class PROJECTION_TYPE
{
    PERSPECTIVE,
    ORTHOGRAPHIC,

};

struct MapSize
{
    float MapSizeX = 0.f;
    float MapSizeY = 0.f;

};


class Camera :
    public Component
{

public:
    Camera();

public:
    void Update() override;
    void LateUpdate() override;
    void SetMapSize(float _x, float _y) { currentMapSize = { _x,_y }; }

public:
    void SetCameraObject(shared_ptr<class GameObject> _object) { mCameraObject = _object; }
public:
    static XMMATRIX GetViewMatrix() { return mViewMatrix; }
    static XMMATRIX GetProjectionMatrix() { return mProjectionMatrix; }
private:
    float _near = 1.f;
    float _far = 1000.f;
    float _fov = XM_PI / 4.f;
    float _scale = 1.f;
    float _width = 0.f;
    float _height = 0.f;



private:
    static XMMATRIX mViewMatrix;
    static XMMATRIX mProjectionMatrix;
    MapSize currentMapSize = { 0.f,0.f };

private:
    shared_ptr<class GameObject> mCameraObject;
};

