#ifndef _CameraManager
#define _CameraManager

#include "AzulCore.h"

#include "..\Lemon.h"

class CameraManager
{
public:
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator = (const CameraManager&) = delete;
	~CameraManager();

private: 
	Camera*							m_pActiveCamera;
	Camera*							m_pDefaultCamera;
	Camera*							m_pSpriteCamera;

public:
	Camera*							GetActiveCamera();
	void							SetActiveCamera(Camera* pCam);
	void							SetActiveCameraToDefault();
	Camera*							GetSpriteCamera();
};

#endif _CameraManager