#include "BossTank.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "../Lemon.h"
#include "BossBulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Tools/Colors.h"
#include "DemoStartScene.h"
#include "PlayerTank.h"
#include "Time Management/TimeManager.h"
#include "LevelTracker.h"
#include "Sprite/Sprite.h"

BossTank::BossTank()
	: m_health(m_maxHealth), m_turretRot(Matrix(ROT_Y, 0)), m_volleyFired(0)
{
	m_colliding = false;

	m_pHealthbar = new Sprite("red");
	m_pHealthbar->SetPos(Lemon::GetWidth() / 2.0f, Lemon::GetHeight() - 60.0f);
	m_pHealthbar->SetScaleFactor((Lemon::GetWidth() / 4.0f) * 3.0f, 16.0f);

	// Set up tank hull and turret graphics objects
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pHull = new GraphicsObject_TextureLight(ModelManager::Get("tank_hull_boss"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_hull"),
		LightColor,
		LightPos);
	m_pTurret = new GraphicsObject_TextureLight(ModelManager::Get("tank_turret_boss"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);
	m_pGun = new GraphicsObject_TextureLight(ModelManager::Get("tank_gun_boss"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);

	// hull
	m_tankRotTrans = Matrix(ROT_Y, MATH_PI) * Matrix(TRANS, 0, 0, 0);
	Matrix world = m_tankRotTrans;
	m_pHull->SetWorld(world);

	// turret
	m_pTurret->SetWorld(world);
	m_turretRot = Matrix(ROT_Y, MATH_PI);

	// gun
	world = Matrix(TRANS, m_gunOffset) * m_tankRotTrans;
	m_pGun->SetWorld(world);

	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();

	Collidable::SetCollidableGroup<BossTank>();
	Collidable::SetCollisionModel(m_pHull->getModel(), AABB);
	Collidable::UpdateCollisionData(m_tankScale * Matrix(ROT_Y, MATH_PI));
	Collidable::SubmitRegistration();

	// Shoot at player AI
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 1.0f);
}

BossTank::~BossTank()
{
	delete m_pHealthbar;
	delete m_pHull;
	delete m_pTurret;
	delete m_pGun;
}

void BossTank::StartVolley()
{
	m_volleyFired = 0;
}

void BossTank::EndVolley()
{

}

void BossTank::Draw2D()
{
	m_pHealthbar->Render();
}

void BossTank::Draw3D()
{
	m_pHull->Render(SceneManager::GetActiveCamera());
	m_pTurret->Render(SceneManager::GetActiveCamera());
	m_pGun->Render(SceneManager::GetActiveCamera());

	if (m_colliding)
	{
		Visualizer::ShowCollisionVolume(GetCollisionVolume(), Colors::Red);
	}
	else
	{
		//Visualizer::ShowBSphere(GetBSphere());
	}
	m_colliding = false;
}

void BossTank::Update()
{

	// update hull position
	Matrix world = m_tankRotTrans;
	m_pHull->SetWorld(world);

	// update hull collision
	UpdateCollisionData(world);

	// Update turret position relative to hull
	world = Matrix(TRANS, m_turretOffset) * m_tankRotTrans;
	world = m_turretRot * Matrix(TRANS, world.get(ROW_3));
	m_pTurret->SetWorld(world);

	// update gun position relative to turret
	m_gunPos = m_gunOffset * world;
	world = m_turretRot * Matrix(TRANS, m_gunPos);
	m_pGun->SetWorld(world);


}

void BossTank::Alarm0()
{
	int roll = rand() % 100;
	if (roll < 30)
	{
		DebugMsg::out("Firing volley!\n");
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 0.5f);
	}
	else
	{
		Vect playerPos = LevelTracker::GetPlayer()->GetPos();
		playerPos[y] += 135.0f;
		Vect aimDir = playerPos - m_gunPos;
		aimDir.norm();
		// set turret
		m_turretRot = Matrix(ROT_ORIENT, aimDir, Vect(0, 1, 0));

		BossBulletFactory::CreateBossBullet(m_gunPos, aimDir);

		DebugMsg::out("Firing at player!\n");

		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 5.0f);
	}
}

void BossTank::Alarm1()
{
	if (m_volleyFired == m_volleyTotal)
	{
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_2, 0.25f);

		Vect playerPos = LevelTracker::GetPlayer()->GetPos();
		playerPos[y] += 135.0f;
		Vect aimDir = playerPos - m_gunPos;
		aimDir.norm();
		// set turret
		m_turretRot = Matrix(ROT_ORIENT, aimDir, Vect(0, 1, 0));

		BossBulletFactory::CreateBossBullet(m_gunPos, aimDir);
		return;
	}
	m_turretRot = Matrix(ROT_Y, (MATH_2PI / m_volleyTotal) * m_volleyFired);
	Vect aimPoint = Vect(0, 2000, 750) * m_turretRot;
	Vect aimDir = aimPoint - m_gunPos;
	//BossBulletFactory::CreateBossBullet(Matrix(ROT_ORIENT, aimDir, Vect(0, 1, 0)) * Matrix(TRANS, m_gunPos));
	BossBulletFactory::CreateBossBullet(m_gunPos, aimDir);
	m_turretRot = Matrix(ROT_ORIENT, aimDir, Vect(0, 1, 0));
	m_volleyFired++;
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 0.15f);
}

void BossTank::Alarm2()
{
	if (m_volleyFired > 0)
	{
		float rad = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / MATH_2PI));
		float dist = 4200.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (4200.0f - 200.0f)));

		Matrix rot = Matrix(ROT_Y, rad);
		Vect pos = Vect(0, 0, 0) * Matrix(TRANS, Vect(0, 5000, dist) * rot);

		BossBulletFactory::CreateBossBullet(pos, Vect(0,-1,0));

		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_2, 0.25f);

		m_volleyFired--;
	}
	else
	{
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 5.0f);
	}
}

void BossTank::Collision(Bullet*)
{
	m_health--;
	m_pHealthbar->SetScaleFactor((float(m_health) / float(m_maxHealth)) * ((Lemon::GetWidth() / 4.0f) * 3.0f), 16.0f);
	if (m_health <= 0)
	{
		Drawable::SubmitDeregistration();
		Updatable::SubmitDeregistration();
		Collidable::SubmitDeregistration();
		if (m_volleyFired > 0) Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_1);
		else Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);

		LevelTracker::BossDestroyed();
		BossBulletFactory::Recall();
	}
}

void BossTank::Initialize(Vect& pos)
{
	Matrix rot = Matrix(IDENTITY);
	Matrix trans = Matrix(TRANS, pos);
	Initialize(rot, trans);
}

void BossTank::Initialize(Matrix& rot, Matrix& trans)
{
	// reset health
	m_health = 20;

	// hull
	m_tankRotTrans = m_tankScale * rot * trans;
	m_pHull->SetWorld(m_tankRotTrans);

	Collidable::UpdateCollisionData(m_tankRotTrans);

	// turret
	m_turretRot = rot;
	Matrix world = m_tankScale * Matrix(TRANS, m_turretOffset) * m_tankRotTrans;
	m_pTurret->SetWorld(world);
}
