#include "Rock6.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Rock6::~Rock6()
{
	delete m_pGraphicsObj;
}

void Rock6::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("rock6"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("rock6"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Rock6>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);

	SubmitEntry();
}

void Rock6::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Rock6::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Rock6::SceneExit()
{
	delete this;
}

void Rock6::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Rock6::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Rock6::Collision(Bullet*)
{
}

void Rock6::Collision(EnemyBullet*)
{
}

void Rock6::Collision(BossBullet*)
{
}

void Rock6::Collision(PlayerTank*)
{
}

void Rock6::Collision(EnemyTank*)
{
}
