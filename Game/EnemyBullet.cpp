#include "EnemyBullet.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "EnemyBulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"

EnemyBullet::EnemyBullet()
{
	// Set up EnemyBullet graphics object
	Vect orange(1.0f, 0.5f, 0.0f, 1.0f);
	m_pGraphicsObj = new GraphicsObject_WireframeConstantColor(
		ModelManager::Get("LEMON_DEFAULT_SPHERE"),
		ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"),
		orange
	);

	SetCollidableGroup<EnemyBullet>();
	Collidable::SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);
}

EnemyBullet::~EnemyBullet()
{
	delete m_pGraphicsObj;
}

void EnemyBullet::Initialize(Matrix rotTrans)
{
	m_scale.set(SCALE, 10.0f, 10.0f, 10.0f);
	m_rotTrans = rotTrans;
	Matrix world = m_scale * m_rotTrans;
	m_pGraphicsObj->SetWorld(world);

	SubmitEntry();
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 5.0f);

	Collidable::UpdateCollisionData(world);
	Collidable::SubmitRegistration();
}

void EnemyBullet::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void EnemyBullet::Update()
{
	m_rotTrans = Matrix(TRANS, Vect(0, 0, m_speed)) * m_rotTrans;
	Matrix world = m_scale * m_rotTrans;
	m_pGraphicsObj->SetWorld(world);
	Collidable::UpdateCollisionData(world);
}

void EnemyBullet::Alarm0()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	SubmitExit();
}

void EnemyBullet::SceneExit()
{
	EnemyBulletFactory::RecycleEnemyBullet(this);
}

void EnemyBullet::Collision(PlayerTank*)
{
	DebugMsg::out("EnemyBullet collided with Player\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(BossTank*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(BuildingA*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(BuildingB*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(Container*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(WallA*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void EnemyBullet::Collision(WallB*)
{
	DebugMsg::out("EnemyBullet collided with Obstacle\n");
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

//void EnemyBullet::Collision(Obstacle*)
//{
//	DebugMsg::out("EnemyBullet collided with Obstacle\n");
//	Drawable::SubmitDeregistration();
//	Updatable::SubmitDeregistration();
//	Collidable::SubmitDeregistration();
//	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
//	SubmitExit();
//}
