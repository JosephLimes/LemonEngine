#include "WallB.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

WallB::~WallB()
{
	delete m_pGraphicsObj;
}

void WallB::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("wall_b"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("wall_b"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<WallB>();
	SetCollisionModel(m_pGraphicsObj->getModel(), OBB);

	SubmitEntry();
}

void WallB::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void WallB::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void WallB::SceneExit()
{
	delete this;
}

void WallB::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void WallB::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void WallB::Collision(Bullet*)
{
}

void WallB::Collision(EnemyBullet*)
{
}

void WallB::Collision(BossBullet*)
{
}

void WallB::Collision(PlayerTank*)
{
}

void WallB::Collision(EnemyTank*)
{
}
