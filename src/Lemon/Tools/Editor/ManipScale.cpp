#include "ManipScale.h"
#include "EditorAdmin.h"
#include "Time Management/TimeManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

ManipScale::ManipScale(EditorAdmin* pAdmin)
{
	m_pAdmin = pAdmin;
	m_pEnds = new GraphicsObject_TextureFlat(ModelManager::Get("scale"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("scale"));
}

ManipScale::~ManipScale()
{
	delete m_pEnds;
}

void ManipScale::ProcessInputs()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float rate = 1.5f * delta;
	Matrix m_input = Matrix(IDENTITY);

	// scale up/down
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		m_input = Matrix(SCALE, 1 + rate, 1 + rate, 1 + rate);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		m_input = Matrix(SCALE, 1 - rate, 1 - rate, 1 - rate);
	}

	
	m_pAdmin->ManipulateSelected(m_input);
	m_input = Matrix(IDENTITY);
}

void ManipScale::Draw()
{
	float scale = m_pAdmin->GetWidgetScaleFactor();
	Matrix world = Matrix(SCALE, Vect(scale, scale, scale)) * m_pAdmin->GetSelectedWorld();
	m_pEnds->SetWorld(world);
	m_pEnds->Render(SceneManager::GetActiveCamera());
}
