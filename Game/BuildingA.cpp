#include "BuildingA.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

BuildingA::~BuildingA()
{
	delete m_pGraphicsObj;
}

void BuildingA::LevelInitialize()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_TextureLight(ModelManager::Get("building_a"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("building_a"),
		LightColor,
		LightPos);
	m_pGraphicsObj->SetWorld(m_world);

	SetCollidableGroup<BuildingA>();
	SetCollisionModel(m_pGraphicsObj->getModel(), OBB);

	SubmitEntry();
}

void BuildingA::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	//Collidable::SubmitDeregistration();

	SubmitExit();
}

void BuildingA::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	//Collidable::SubmitRegistration();
}

void BuildingA::SceneExit()
{
	delete this;
}

void BuildingA::Update()
{
	m_pGraphicsObj->SetWorld(m_world);
	UpdateCollisionData(m_world);
}

void BuildingA::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void BuildingA::Collision(Bullet*)
{
}

void BuildingA::Collision(EnemyBullet*)
{
}

void BuildingA::Collision(BossBullet*)
{
}

void BuildingA::Collision(PlayerTank*)
{
}

void BuildingA::Collision(EnemyTank*)
{
}
