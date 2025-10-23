#include "CameraManager.h"

CameraManager::CameraManager()
{
	// set up default camera
	m_pDefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	Lemon::GetHeight();
	m_pDefaultCamera->setViewport(0, 0, Lemon::GetWidth(), Lemon::GetHeight());
	m_pDefaultCamera->setPerspective(35.0f, float(Lemon::GetWidth()) / float(Lemon::GetHeight()), 1.0f, 35000.0f);

	// orient and update default camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(0.0f, 250.0f, -175.0f);
	Vect lookAt3DCam(0.0f, 30.0f, 300.0f);
	m_pDefaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	m_pDefaultCamera->updateCamera();

	// set active camera to default
	m_pActiveCamera = m_pDefaultCamera;

	// set up sprite camera
	m_pSpriteCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

	m_pSpriteCamera->setViewport(0, 0, Lemon::GetWidth(), Lemon::GetHeight());
	m_pSpriteCamera->setOrthographic(-0.5f * Lemon::GetWidth(), 0.5f * Lemon::GetWidth(), -0.5f * Lemon::GetHeight(), 0.5f * Lemon::GetHeight(), 1.0f, 1000.0f);

	// orient and update sprite camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	m_pSpriteCamera->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	m_pSpriteCamera->updateCamera();
}

CameraManager::~CameraManager()
{
	delete m_pDefaultCamera;
	delete m_pSpriteCamera;
}

Camera* CameraManager::GetActiveCamera()
{
	return m_pActiveCamera;
}

void CameraManager::SetActiveCamera(Camera* pCam)
{
	m_pActiveCamera = pCam;
}

void CameraManager::SetActiveCameraToDefault()
{
	m_pActiveCamera = m_pDefaultCamera;
}

Camera* CameraManager::GetSpriteCamera()
{
	return m_pSpriteCamera;
}
