#include "GodCam.h"
#include "../Lemon.h"
#include "Time Management/TimeManager.h"

#include "Tools/ScreenLog/ScreenLog.h"
#include "Tools/LemonMath.h"

GodCam::GodCam()
	: 
	m_pCam(new Camera(Camera::Type::PERSPECTIVE_3D)),
	m_rot(Matrix(IDENTITY)),
	m_up(Vect(0,1,0)),
	m_pos(Vect(0.0f, 15.0f, -75.0f)),
	m_dir(Vect(0,0,10))
{
	m_pCam->setViewport(0, 0, Lemon::GetWidth(), Lemon::GetHeight());
	m_pCam->setPerspective(35.0f, float(Lemon::GetWidth()) / float(Lemon::GetHeight()), 1.0f, 10000.0f);
	m_pCam->setOrientAndPosition(Vect(0, 1, 0), m_pos - m_dir, m_pos);
	m_pCam->updateCamera();

	Updatable::SubmitRegistration();

	Inputable::SubmitRegistration(AZUL_KEY::KEY_C, KeyEvent::KEY_PRESS);
}

GodCam::~GodCam()
{
	delete m_pCam;
}

void GodCam::Update()
{
	float frameTransSpeed = m_transSpeed * TimeManager::GetFrameTime();

	// Camera translation movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		m_pos += Vect(0, 0, 1) * m_rot * frameTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		m_pos += Vect(0, 0, 1) * m_rot * -frameTransSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		m_pos += Vect(1, 0, 0) * m_rot * frameTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		m_pos += Vect(1, 0, 0) * m_rot * -frameTransSpeed;
	}

	// Camera Rotation movement via keys
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		m_rot *= Matrix(ROT_Y, m_rotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		m_rot *= Matrix(ROT_Y, -m_rotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		m_rot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * m_rot, -m_rotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		m_rot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * m_rot, m_rotSpeed);
	}

	// Update the camera settings
	m_pCam->setOrientAndPosition(m_up * m_rot, m_pos + m_dir * m_rot, m_pos);
	m_pCam->updateCamera();
}

void GodCam::SetActive()
{
	SceneManager::SetActiveCamera(m_pCam);
}

void GodCam::KeyPressed(AZUL_KEY key)
{
	key;
	// key is c
	SetActive();
}
