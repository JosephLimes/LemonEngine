#include "Axis.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Scene/SceneManager.h"

#include "Tools/Colors.h"
#include "Tools/Visualizer/Visualizer.h"

#include "TextureTGA.h"

Axis::Axis()
	: m_colliding(false)
{
	Drawable::SubmitRegistration();

	m_pBase = new GraphicsObject_TextureFlat(ModelManager::Get("widget"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("widget"));
	//Matrix world = Matrix(ROT_Y, 20) * Matrix(TRANS, 0, 10, 0);
	Matrix world = Matrix(IDENTITY);
	m_pBase->SetWorld(world);

	m_pArrows = new GraphicsObject_TextureFlat(ModelManager::Get("translate"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("move"));
	m_pArrows->SetWorld(world);

	SetCollidableGroup<Axis>();
	SetCollisionModel(m_pBase->getModel(), OBB);
	Collidable::SubmitRegistration();
	UpdateCollisionData(world);
}

void Axis::Draw3D()
{
	if (m_colliding)
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume(), Colors::Red);
	}
	else
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume());
	}
	m_colliding = false;
	m_pBase->Render(SceneManager::GetActiveCamera());
	m_pArrows->Render(SceneManager::GetActiveCamera());

}

void Axis::Collision(Frigate* pFrigate)
{
	pFrigate;
	m_colliding = true;
}

void Axis::SetWorld(Matrix& world)
{
	m_pBase->SetWorld(world);
	m_pArrows->SetWorld(world);
	UpdateCollisionData(world);
}

Axis::~Axis()
{
	delete m_pBase;
	delete m_pArrows;
}