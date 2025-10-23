#include "WallA.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

WallA::~WallA()
{
	delete m_pGraphicsObj;
}

void WallA::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("wall_a"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("wall_a"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<WallA>();
	SetCollisionModel(m_pGraphicsObj->getModel(), OBB);

	SubmitEntry();
}

void WallA::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void WallA::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void WallA::SceneExit()
{
	delete this;
}

void WallA::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void WallA::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void WallA::Collision(Bullet*)
{
}

void WallA::Collision(EnemyBullet*)
{
}

void WallA::Collision(BossBullet*)
{
}

void WallA::Collision(PlayerTank*)
{
}

void WallA::Collision(EnemyTank*)
{
}
