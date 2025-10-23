#include "BossBullet.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"
#include "Scene/SceneManager.h"
#include "BossBulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"

BossBullet::BossBullet()
{
	// Set up BossBullet graphics object
	m_pGraphicsObj = new GraphicsObject_TextureFlat(
		ModelManager::Get("LEMON_DEFAULT_SPHERE"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE"),
		TextureManager::Get("red")
	);

	SetCollidableGroup<BossBullet>();
	Collidable::SetCollisionModel(m_pGraphicsObj->getModel(), BSPHERE);
}

BossBullet::~BossBullet()
{
	delete m_pGraphicsObj;
}

void BossBullet::Initialize(Vect pos, Vect dir)
{
	m_pos = pos;
	m_dir = dir;
	m_dir.norm();
	m_scale.set(SCALE, 150.0f, 150.0f, 150.0f);
	m_rotTrans = Matrix(TRANS, pos);
	Matrix world = m_scale * m_rotTrans;
	m_pGraphicsObj->SetWorld(world);

	SubmitEntry();
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 15.0f);

	Collidable::UpdateCollisionData(world);
	Collidable::SubmitRegistration();
}

void BossBullet::Draw3D()
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

void BossBullet::Update()
{
	//m_rotTrans = Matrix(TRANS, Vect(0, 0, m_speed)) * m_rotTrans;
	m_pos = m_pos + (m_dir * m_speed);
	m_rotTrans = Matrix(TRANS, m_pos);
	Matrix world = m_scale * m_rotTrans;
	m_pGraphicsObj->SetWorld(world);
	Collidable::UpdateCollisionData(world);
}

void BossBullet::Alarm0()
{
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 5.0f);
	SubmitExit();
}

void BossBullet::SceneExit()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
	Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
	BossBulletFactory::RecycleBossBullet(this);
}

void BossBullet::Collision(PlayerTank*)
{
	DebugMsg::out("BossBullet collided with Player\n");
	SubmitExit();
}

void BossBullet::Collision(Obstacle*)
{
	DebugMsg::out("BossBullet collided with Obstacle\n");
	SubmitExit();
}
