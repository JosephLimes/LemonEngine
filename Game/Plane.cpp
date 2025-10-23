#include "Plane.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Scene/SceneManager.h"

Plane::Plane()
{
	Drawable::SubmitRegistration();

	m_pGraphicsObj = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("Plane"));
	//Matrix world = Matrix(SCALE, 1.0f, 1.0f, 1.0f);

	Matrix world = Matrix(IDENTITY);
	m_pGraphicsObj->SetWorld(world);
}

void Plane::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

Plane::~Plane()
{
	delete m_pGraphicsObj;
}