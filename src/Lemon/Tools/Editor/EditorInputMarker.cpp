#include "EditorInputMarker.h"
#include "EditorAdmin.h"
#include "Time Management/TimeManager.h"

EditorInputMarker::EditorInputMarker(EditorAdmin* pAdmin)
{
	this->m_pAdmin = pAdmin;
}

void EditorInputMarker::ProcessInputs()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float speed = m_pAdmin->GetSpeed() * 150.0f * delta;
	float rotspeed = 7.5f * delta;

	Matrix world = m_pAdmin->GetMarkerWorld();

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		world = Matrix(ROT_Y, (rotspeed)) * world;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		world = Matrix(ROT_Y, -rotspeed) * world;
	}
	// forward back move
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		world = Matrix(TRANS, Vect(0, 0, speed)) * world;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		world = Matrix(TRANS, Vect(0, 0, -speed)) * world;
	}
	// up down move
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT))
	{
		world = Matrix(TRANS, Vect(0, speed, 0)) * world;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL))
	{
		world = Matrix(TRANS, Vect(0, -speed, 0)) * world;
	}

	m_pAdmin->SetMarkerWorld(world);
}