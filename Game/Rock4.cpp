#include "Rock4.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Rock4::~Rock4()
{
	delete m_pGraphicsObj;
}

void Rock4::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("rock4"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("rock4"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Rock4>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);

	SubmitEntry();
}

void Rock4::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Rock4::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Rock4::SceneExit()
{
	delete this;
}

void Rock4::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Rock4::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Rock4::Collision(Bullet*)
{
}

void Rock4::Collision(EnemyBullet*)
{
}

void Rock4::Collision(BossBullet*)
{
}

void Rock4::Collision(PlayerTank*)
{
}

void Rock4::Collision(EnemyTank*)
{
}
