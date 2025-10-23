#include "BuildingB.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

BuildingB::~BuildingB()
{
	delete m_pGraphicsObj;
}

void BuildingB::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("building_b"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("building_b"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<BuildingB>();
	SetCollisionModel(m_pGraphicsObj->getModel(), OBB);

	SubmitEntry();
}

void BuildingB::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void BuildingB::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void BuildingB::SceneExit()
{
	delete this;
}

void BuildingB::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void BuildingB::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void BuildingB::Collision(Bullet*)
{
}

void BuildingB::Collision(EnemyBullet*)
{
}

void BuildingB::Collision(BossBullet*)
{
}

void BuildingB::Collision(PlayerTank*)
{
}

void BuildingB::Collision(EnemyTank*)
{
}
