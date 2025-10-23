#include "EditorCam.h"
#include "EditorAdmin.h"
#include "../Lemon.h"
#include "Time Management/TimeManager.h"
#include "Scene/SceneManager.h"

EditorCam::EditorCam(EditorAdmin* pAdmin)
:	m_pAdmin(pAdmin),
	m_pCam(new Camera(Camera::Type::PERSPECTIVE_3D)),
	m_camrot(Matrix(IDENTITY)),
	m_camup(Vect(0, 1, 0)),
	m_campos(Vect(0.0f, 15.0f, -75.0f)),
	m_camdir(Vect(0, 0, 10))
{
	m_pCam->setViewport(0, 0, Lemon::GetWidth(), Lemon::GetHeight());
	m_pCam->setPerspective(35.0f, float(Lemon::GetWidth()) / float(Lemon::GetHeight()), 1.0f, 35000.0f);
	m_pCam->setOrientAndPosition(Vect(0, 1, 0), m_campos - m_camdir, m_campos);
	m_pCam->updateCamera();
	SceneManager::SetActiveCamera(m_pCam);
}

EditorCam::~EditorCam()
{
	delete m_pCam;
}

void EditorCam::ProcessInputs()
{
	float delta = TimeManager::GetFrameTime();
	float speed = m_pAdmin->GetSpeed() * m_transSpeed * delta;

	// cam rotation via mouse
	int x, y;
	Lemon::getMousePosition(x, y);

	int centerX = Lemon::GetWidth() / 2;
	int centerY = Lemon::GetHeight() / 2;

	glfwSetMousePos(centerX, centerY);

	float yaw = float(centerX - x) * m_rotSpeed * 0.001f;
	float pitch = float(centerY - y) * m_rotSpeed * 0.001f;

	m_camrot *= Matrix(ROT_Y, yaw);
	m_camrot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * m_camrot, -pitch);

	// Camera translation movement
	// forward/back
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		m_campos += Vect(0, 0, 1) * m_camrot * speed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		m_campos += Vect(0, 0, 1) * m_camrot * -speed;
	}
	// strafe left/right
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		m_campos += Vect(1, 0, 0) * m_camrot * speed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		m_campos += Vect(1, 0, 0) * m_camrot * -speed;
	}
	// up/down
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT))
	{
		m_campos += Vect(0, 1, 0) * speed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL))
	{
		m_campos -= Vect(0, 1, 0) * speed;
	}

	// Update the camera settings
	m_pCam->setOrientAndPosition(m_camup * m_camrot, m_campos + m_camdir * m_camrot, m_campos);
	m_pCam->updateCamera();
}

Matrix EditorCam::GetProjMatrix()
{
	return m_pCam->getProjMatrix();
}

Matrix EditorCam::GetViewMatrix()
{
	return m_pCam->getViewMatrix();
}
