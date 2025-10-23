#include "Rock1.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Rock1::~Rock1()
{
	delete m_pGraphicsObj;
}

void Rock1::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("rock1"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("rock1"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Rock1>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);

	SubmitEntry();
}

void Rock1::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Rock1::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Rock1::SceneExit()
{
	delete this;
}

void Rock1::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Rock1::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Rock1::Collision(Bullet*)
{
}

void Rock1::Collision(EnemyBullet*)
{
}

void Rock1::Collision(BossBullet*)
{
}

void Rock1::Collision(PlayerTank*)
{
}

void Rock1::Collision(EnemyTank*)
{
}
