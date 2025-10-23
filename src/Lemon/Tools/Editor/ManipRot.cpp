#include "ManipRot.h"
#include "EditorAdmin.h"
#include "Time Management/TimeManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

ManipRot::ManipRot(EditorAdmin* pAdmin)
{
	this->m_pAdmin = pAdmin;
	m_pGO = new GraphicsObject_TextureFlat(ModelManager::Get("rotate"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("rotate"));
}

ManipRot::~ManipRot()
{
	delete m_pGO;
}

void ManipRot::ProcessInputs()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float speed = 2.5f * delta;
	Matrix input = Matrix(IDENTITY);

	// left right turn
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		input *= Matrix(ROT_AXIS_ANGLE, Vect(0, 1, 0), speed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		input *= Matrix(ROT_AXIS_ANGLE, Vect(0, 1, 0), -speed);
	}
	// up down tilt
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		input *= Matrix(ROT_X, speed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		input *= Matrix(ROT_X, -speed);
	}


	m_pAdmin->ManipulateSelected(input);
}

void ManipRot::Draw()
{
	float scale = m_pAdmin->GetWidgetScaleFactor();
	Matrix world = Matrix(SCALE, Vect(scale, scale, scale)) * m_pAdmin->GetSelectedWorld();
	m_pGO->SetWorld(world);
	m_pGO->Render(SceneManager::GetActiveCamera());
}
