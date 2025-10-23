#include "Bullet.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "BulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"

Bullet::Bullet()
{
	// Set up bullet graphics object
	Vect color = Colors::Aqua;
	m_pGraphicsObj = new GraphicsObject_WireframeConstantColor(
		ModelManager::Get("LEMON_DEFAULT_SPHERE"),
		ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"),
		color
	);

	SetCollidableGroup<Bullet>();
	SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);
}

Bullet::~Bullet()
{
	delete m_pGraphicsObj;
}

void Bullet::Initialize(Matrix rotTrans)
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

void Bullet::Draw3D()
{
	m_pGraphicsObj->Render(SceneManager::GetActiveCamera());

	
	//if (m_colliding)
	//{
	//	Visualizer::ShowBSphere(GetBSphere(), Colors::Red);
	//}
	//else
	//{
	//	Visualizer::ShowBSphere(GetBSphere());
	//}
	//m_colliding = false;
}

void Bullet::Update()
{
	m_rotTrans = Matrix(TRANS, Vect(0, 0, m_speed)) * m_rotTrans;
	Matrix world = m_scale * m_rotTrans;
	m_pGraphicsObj->SetWorld(world);
	Collidable::UpdateCollisionData(world);
}

void Bullet::Alarm0()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	SubmitExit();
}

void Bullet::SceneExit()
{
	BulletFactory::RecycleBullet(this);
}

void Bullet::Collision(EnemyTank*)
{
	DebugMsg::out("Bullet collided with EnemyTank.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(BossTank*)
{
	DebugMsg::out("Bullet collided with BossTank.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(BuildingA*)
{
	DebugMsg::out("Bullet collided with Obstacle.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(BuildingB*)
{
	DebugMsg::out("Bullet collided with Obstacle.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(Container*)
{
	DebugMsg::out("Bullet collided with Obstacle.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(WallA*)
{
	DebugMsg::out("Bullet collided with Obstacle.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

void Bullet::Collision(WallB*)
{
	DebugMsg::out("Bullet collided with Obstacle.\n");

	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	SubmitExit();
}

//void Bullet::Collision(Obstacle*)
//{
//	DebugMsg::out("Bullet collided with Obstacle.\n");
//
//	Drawable::SubmitDeregistration();
//	Updatable::SubmitDeregistration();
//	Collidable::SubmitDeregistration();
//	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
//	SubmitExit();
//}
