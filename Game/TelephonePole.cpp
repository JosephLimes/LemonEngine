#include "TelephonePole.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

TelephonePole::~TelephonePole()
{
	delete m_pGraphicsObj;
}

void TelephonePole::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("telephone_pole"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("telephone_pole"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<TelephonePole>();
	SetCollisionModel(m_pGraphicsObj->getModel(), AABB);

	SubmitEntry();
}

void TelephonePole::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void TelephonePole::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void TelephonePole::SceneExit()
{
	delete this;
}

void TelephonePole::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void TelephonePole::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void TelephonePole::Collision(Bullet*)
{
}

void TelephonePole::Collision(EnemyBullet*)
{
}

void TelephonePole::Collision(BossBullet*)
{
}

void TelephonePole::Collision(PlayerTank*)
{
}

void TelephonePole::Collision(EnemyTank*)
{
}
