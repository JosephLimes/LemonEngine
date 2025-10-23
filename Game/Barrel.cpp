#include "Barrel.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Barrel::~Barrel()
{
	delete m_pGraphicsObj;
}

void Barrel::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("barrel"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("barrel"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<Barrel>();
	SetCollisionModel(m_pGraphicsObj->getModel(), AABB);

	SubmitEntry();
}

void Barrel::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Barrel::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Barrel::SceneExit()
{
	delete this;
}

void Barrel::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Barrel::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void Barrel::Collision(Bullet*)
{
}

void Barrel::Collision(EnemyBullet*)
{
}

void Barrel::Collision(BossBullet*)
{
}

void Barrel::Collision(PlayerTank*)
{
}

void Barrel::Collision(EnemyTank*)
{
}
