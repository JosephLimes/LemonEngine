#include "Rock2.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Rock2::~Rock2()
{
	delete m_pGraphicsObj;
}

void Rock2::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("rock2"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("rock2"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Rock2>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);

	SubmitEntry();
}

void Rock2::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Rock2::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Rock2::SceneExit()
{
	delete this;
}

void Rock2::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Rock2::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Rock2::Collision(Bullet*)
{
}

void Rock2::Collision(EnemyBullet*)
{
}

void Rock2::Collision(BossBullet*)
{
}

void Rock2::Collision(PlayerTank*)
{
}

void Rock2::Collision(EnemyTank*)
{
}
