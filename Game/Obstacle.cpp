#include "Obstacle.h"
#include "Scene/SceneManager.h"
#include "Tools/Visualizer/Visualizer.h"

Obstacle::Obstacle(GraphicsObject_TextureFlat* pGO, Matrix& world)
	: m_pGraphicsObj(pGO)
{
		m_pGraphicsObj->SetWorld(world);
		Drawable::SubmitRegistration();
		Collidable::SetCollisionModel(pGO->getModel(), BSPHERE);
		Collidable::UpdateCollisionData(world);
		Collidable::SetCollidableGroup<Obstacle>();
		Collidable::SubmitRegistration();
}

void Obstacle::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
	//Visualizer::ShowBSphere(GetBSphere());
}

void Obstacle::Collision(Bullet*)
{}

void Obstacle::Collision(EnemyBullet*)
{}

void Obstacle::Collision(BossBullet*)
{}

Obstacle::~Obstacle()
{
	delete m_pGraphicsObj;
}
