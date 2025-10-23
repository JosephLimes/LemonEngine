#include "EnemyTank.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "../Lemon.h"
#include "EnemyBulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Tools/Colors.h"
#include "DemoStartScene.h"
#include "PlayerTank.h"
#include "Time Management/TimeManager.h"
#include "LevelTracker.h"

EnemyTank::EnemyTank()
	: m_health(3), m_turretRot(Matrix(ROT_Y, 0)), m_aimDir(Vect(0,0,1)), m_gunRot(Matrix(IDENTITY))
{
	m_moveState = NOT_MOVING;
	m_colliding = false;

	// graphics objects
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pHull = new GraphicsObject_TextureLight(ModelManager::Get("tank_hull"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_hull"),
		LightColor,
		LightPos);
	m_pTurret = new GraphicsObject_TextureLight(ModelManager::Get("tank_turret"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);
	m_pGun = new GraphicsObject_TextureLight(ModelManager::Get("tank_gun"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_enemy_turretgun"),
		LightColor,
		LightPos);

	// hull
	m_tankRotTrans = Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 0, 0);
	Matrix world = m_tankRotTrans;
	m_pHull->SetWorld(world);

	// turret
	m_pTurret->SetWorld(world);

	// gun
	world = Matrix(TRANS, m_gunOffset) * m_tankRotTrans;
	m_pGun->SetWorld(world);

	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();

	Collidable::SetCollidableGroup<EnemyTank>();
	Collidable::SetCollisionModel(m_pHull->getModel(), BSPHERE);
	Collidable::SubmitRegistration();

	// Shoot at player AI
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 1.0f);
	// Movement AI
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 3.0f);
}

EnemyTank::~EnemyTank()
{
	delete m_pHull;
	delete m_pTurret;
	delete m_pGun;
}

void EnemyTank::Draw3D()
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

void EnemyTank::Update()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float frameTankTransSpeed = m_tankTransSpeed * delta;
	float frameTankRotSpeed = m_tankRotSpeed * delta;

	switch (m_moveState)
	{
	case NOT_MOVING:
		// do nothing :)
		break;
	case MOVE_FORWARD:
		m_tankRotTrans = Matrix(TRANS, Vect(0, 0, frameTankTransSpeed)) * m_tankRotTrans;
		break;
	case MOVE_BACK:
		m_tankRotTrans = Matrix(TRANS, Vect(0, 0, -frameTankTransSpeed)) * m_tankRotTrans;
		break;
	case TURN_LEFT:
		m_tankRotTrans = Matrix(ROT_Y, (frameTankRotSpeed)) * m_tankRotTrans;
		break;
	case TURN_RIGHT:
		m_tankRotTrans = Matrix(ROT_Y, -frameTankRotSpeed) * m_tankRotTrans;
		break;
	}

	// Update tank matrix to conform to terrain
	Vect pos = m_tankRotTrans.get(ROW_3);
	Vect n = SceneManager::GetActiveScene().TerrainNormAt(pos);
	float h = SceneManager::GetActiveScene().TerrainHeightAt(pos);
	Vect r = n.cross(m_tankRotTrans.get(ROW_2));
	Vect up = r.cross(n);
	pos[y] = h;
	m_tankRotTrans = Matrix(ROT_ORIENT, up, n) * Matrix(TRANS, pos);

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

void EnemyTank::Alarm0()
{
	if ((rand() % 100) < 20) // 1/5 chance to attack
	{
		Vect playerPos = LevelTracker::GetPlayer()->GetPos();
		playerPos[y] += 135.0f;
		m_aimDir = playerPos - m_gunPos;
		m_aimDir.norm();
		// set turret
		m_turretRot = Matrix(ROT_ORIENT, m_aimDir, Vect(0, 1, 0));

		EnemyBulletFactory::CreateEnemyBullet(Matrix(ROT_ORIENT, m_aimDir, Vect(0, 1, 0)) * Matrix(TRANS, m_gunPos));

		DebugMsg::out("Firing at player!\n");
	}

	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 1.0f);
}

void EnemyTank::Alarm1()
{
	int seed = rand() % 100;

	// 10% chance to move forward, backward, turn left, or turn right, total 40% to move
	// 60% chance to stand still

	if (seed < 10)
	{
		m_moveState = MOVE_FORWARD;
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 2.0f);
	}
	else if (seed < 20)
	{
		m_moveState = MOVE_BACK;
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 2.0f);
	}
	else if (seed < 30)
	{
		m_moveState = TURN_LEFT;
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 1.0f);
	}
	else if (seed < 40)
	{
		m_moveState = TURN_RIGHT;
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 1.0f);
	}
	else
	{
		m_moveState = NOT_MOVING;
		Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 2.0f);
	}
}

void EnemyTank::Collision(Bullet*)
{
	m_health--;
	if (m_health <= 0)
	{
		Drawable::SubmitDeregistration();
		Updatable::SubmitDeregistration();
		Collidable::SubmitDeregistration();
		Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_0);
		Alarmable::SubmitDeregistration(AlarmableManager::AlarmID::ALARM_1);

		LevelTracker::EnemyDestroyed();
	}
}

void EnemyTank::Initialize(Vect& pos)
{
	Matrix rot = Matrix(IDENTITY);
	Matrix trans = Matrix(TRANS, pos);
	Initialize(rot, trans);
}

void EnemyTank::Initialize(Matrix& rot, Matrix& trans)
{
	// reset health
	m_health = 3;

	// hull
	m_tankRotTrans = rot * trans;
	m_pHull->SetWorld(m_tankRotTrans);

	Collidable::UpdateCollisionData(m_tankRotTrans);

	// turret
	m_turretRot = rot;
	Matrix world = Matrix(TRANS, m_turretOffset) * m_tankRotTrans;
	m_pTurret->SetWorld(world);
}
