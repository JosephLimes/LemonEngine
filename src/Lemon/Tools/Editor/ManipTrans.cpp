#include "ManipTrans.h"
#include "EditorAdmin.h"
#include "Time Management/TimeManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

ManipTrans::ManipTrans(EditorAdmin* pAdmin)
{
	m_pAdmin = pAdmin;
	m_pArrows = new GraphicsObject_TextureFlat(ModelManager::Get("translate"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("move"));
}

ManipTrans::~ManipTrans()
{
	delete m_pArrows;
}

void ManipTrans::ProcessInputs()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float speed = m_pAdmin->GetSpeed() *  150.0f * delta;
	Matrix m_input = Matrix(IDENTITY);

	// left right turn
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		m_input = Matrix(TRANS, Vect(speed, 0, 0)) * m_input;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		m_input = Matrix(TRANS, Vect(-speed, 0, 0)) * m_input;
	}
	// forward back move
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		m_input = Matrix(TRANS, Vect(0, 0, speed)) * m_input;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		m_input = Matrix(TRANS, Vect(0, 0, -speed)) * m_input;
	}
	// up down move
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_SHIFT))
	{
		m_input = Matrix(TRANS, Vect(0, speed, 0)) * m_input;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_LEFT_CONTROL))
	{
		m_input = Matrix(TRANS, Vect(0, -speed, 0)) * m_input;
	}

	m_pAdmin->ManipulateSelected(m_input);
	m_input = Matrix(IDENTITY);
}

void ManipTrans::Draw()
{
	float scale = m_pAdmin->GetWidgetScaleFactor();
	Matrix world = Matrix(SCALE, Vect(scale, scale, scale)) * m_pAdmin->GetSelectedWorld();
	//m_pBase->SetWorld(world);
	m_pArrows->SetWorld(world);
	//m_pBase->Render(SceneManager::GetActiveCamera());
	m_pArrows->Render(SceneManager::GetActiveCamera());
}
