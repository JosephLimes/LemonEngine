#include "Container.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

Container::~Container()
{
	delete m_pGObase;
	delete m_pGOdoorL;
	delete m_pGOdoorR;
}

void Container::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGObase = new GraphicsObject_TextureLight(ModelManager::Get("container_base"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("container_base"),
		LightColor,
		LightPos);
	m_pGOdoorL = new GraphicsObject_TextureLight(ModelManager::Get("container_door_l"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("container_door_l"),
		LightColor,
		LightPos);
	m_pGOdoorR = new GraphicsObject_TextureLight(ModelManager::Get("container_door_r"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("container_door_r"),
		LightColor,
		LightPos);

	m_pGObase->SetWorld(m_world);
	m_pGOdoorL->SetWorld(m_world);
	m_pGOdoorR->SetWorld(m_world);

	SetCollidableGroup<Container>();
	SetCollisionModel(m_pGObase->getModel(), OBB);

	SubmitEntry();
}

void Container::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void Container::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void Container::SceneExit()
{
	delete this;
}

void Container::Update()
{
	m_pGObase->SetWorld(m_world);
	m_pGOdoorL->SetWorld(m_world);
	m_pGOdoorR->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void Container::Draw3D()
{
	m_pGObase->Render(SceneManager::GetActiveCamera());
	m_pGOdoorL->Render(SceneManager::GetActiveCamera());
	m_pGOdoorR->Render(SceneManager::GetActiveCamera());
}

void Container::Collision(Bullet*)
{
}

void Container::Collision(EnemyBullet*)
{
}

void Container::Collision(BossBullet*)
{
}

void Container::Collision(PlayerTank*)
{
}

void Container::Collision(EnemyTank*)
{
}
