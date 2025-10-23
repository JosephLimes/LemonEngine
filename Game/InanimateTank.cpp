#include "InanimateTank.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

InanimateTank::~InanimateTank()
{
	delete m_pGOhull;
	delete m_pGOturret;
	delete m_pGOgun;
}

void InanimateTank::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGOhull = new GraphicsObject_TextureLight(ModelManager::Get("tank_hull"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_hull"),
		LightColor,
		LightPos);
	m_pGOturret = new GraphicsObject_TextureLight(ModelManager::Get("tank_turret"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);
	m_pGOgun = new GraphicsObject_TextureLight(ModelManager::Get("tank_gun"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);

	m_pGOhull->SetWorld(m_world);
	Matrix world = Matrix(TRANS, m_turretOffset) * m_world;
	m_pGOturret->SetWorld(world);
	world = Matrix(TRANS, m_gunOffset) * m_world;
	m_pGOgun->SetWorld(world);

	SetCollidableGroup<InanimateTank>();
	SetCollisionModel(m_pGOhull->getModel(), OBB);

	SubmitEntry();
}

void InanimateTank::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void InanimateTank::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void InanimateTank::SceneExit()
{
	delete this;
}

void InanimateTank::Update()
{
	m_pGOhull->SetWorld(m_world);
	Matrix world = Matrix(TRANS, m_turretOffset) * m_world;
	m_pGOturret->SetWorld(world);
	world = Matrix(TRANS, m_gunOffset) * m_world;
	m_pGOgun->SetWorld(world);
	UpdateCollisionData(m_world);
}

void InanimateTank::Draw3D()
{
	m_pGOhull->Render(SceneManager::GetActiveCamera());
	m_pGOturret->Render(SceneManager::GetActiveCamera());
	m_pGOgun->Render(SceneManager::GetActiveCamera());
}

void InanimateTank::Collision(Bullet*)
{
}

void InanimateTank::Collision(EnemyBullet*)
{
}

void InanimateTank::Collision(BossBullet*)
{
}

void InanimateTank::Collision(PlayerTank*)
{
}

void InanimateTank::Collision(EnemyTank*)
{
}
