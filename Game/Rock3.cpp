#include "Rock3.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Rock3::~Rock3()
{
	delete m_pGraphicsObj;
}

void Rock3::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("rock3"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("rock3"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Rock3>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);

	SubmitEntry();
}

void Rock3::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Rock3::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Rock3::SceneExit()
{
	delete this;
}

void Rock3::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Rock3::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Rock3::Collision(Bullet*)
{
}

void Rock3::Collision(EnemyBullet*)
{
}

void Rock3::Collision(BossBullet*)
{
}

void Rock3::Collision(PlayerTank*)
{
}

void Rock3::Collision(EnemyTank*)
{
}
