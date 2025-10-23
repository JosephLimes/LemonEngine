#include "PlayerTank.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "../Lemon.h"
#include "BulletFactory.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Tools/Colors.h"
#include "Time Management/TimeManager.h"
#include "Tools/ScreenLog/ScreenLog.h"
#include "Sprite/SpriteString.h"
#include "Asset Management/FontManager.h"
#include "LevelTracker.h"
#include "Asset Management/TextureManager.h"
#include "Scene/Scene.h"

PlayerTank::PlayerTank()
	:
		m_health(5),
		m_followCameraActive(true),
		m_turretRot(Matrix(ROT_Y, 0)),
		m_pFollowCam(new Camera(Camera::Type::PERSPECTIVE_3D)),
		m_pStrHealth(new SpriteString(FontManager::Get("stencil_36"), "HEALTH: 5", 0.0f, 0.0f)),
		m_pStrEnemyDestroyed(new SpriteString(FontManager::Get("stencil_36"), "ENEMY DESTROYED!", 0.0f, 0.0f)),
		m_pStrLoss(new SpriteString(FontManager::Get("stencil_36"), "YOU LOSE!", 0.0f, 0.0f)),
		m_pStrWin(new SpriteString(FontManager::Get("stencil_36"), "YOU WIN!", 0.0f, 0.0f))
{
	m_colliding = false;

	// Set up tank hull and turret graphics objects
	Vect green = Colors::Green;

	// graphics objects
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pHull = new GraphicsObject_TextureLight(ModelManager::Get("tank_hull"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_player_hull"),
		LightColor,
		LightPos);
	m_pTurret = new GraphicsObject_TextureLight(ModelManager::Get("tank_turret"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_player_turretgun"),
		LightColor,
		LightPos);
	m_pGun = new GraphicsObject_TextureLight(ModelManager::Get("tank_gun"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("tank_player_turretgun"),
		LightColor,
		LightPos);

	// hull
	m_tankRotTrans = Matrix(TRANS, 50, 0, 0);
	Matrix world = m_tankRotTrans;
	m_pHull->SetWorld(world);

	// turret
	m_pTurret->SetWorld(world);

	// gun
	world = Matrix(TRANS, m_gunOffset) * m_tankRotTrans;
	m_pGun->SetWorld(world);

	// Set up follower cam
	m_pFollowCam->setViewport(0, 0, Lemon::GetWidth(), Lemon::GetHeight());
	m_pFollowCam->setPerspective(35.0f, float(Lemon::GetWidth()) / float(Lemon::GetHeight()), 1.0f, 35000.0f);
	SceneManager::SetActiveCamera(m_pFollowCam);

	// set up hud elements
	// health
	float strWidth = m_pStrHealth->GetWidth();
	m_pStrHealthX = Lemon::GetWidth() / 2 - (strWidth / 2);
	m_pStrHealthY = float(Lemon::GetHeight());
	m_pStrHealth->SetPos(m_pStrHealthX, m_pStrHealthY);
	// enemy destroyed
	m_displayDestroyed = false;
	strWidth = m_pStrEnemyDestroyed->GetWidth();
	m_pStrEnemyDestroyed->SetPos(Lemon::GetWidth() / 2 - (strWidth / 2), m_pStrHealthY - 125.0f);
	// you lose
	m_displayLoss = false;
	strWidth = m_pStrLoss->GetWidth();
	m_pStrLoss->SetPos(Lemon::GetWidth() / 2 - (strWidth / 2), Lemon::GetHeight() / 2.0f);
	// you win
	m_displayWin = false;
	strWidth = m_pStrWin->GetWidth();
	m_pStrWin->SetPos(Lemon::GetWidth() / 2 - (strWidth / 2), (Lemon::GetHeight() / 2.0f) + 45.0f);

	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	Inputable::SubmitRegistration(AZUL_KEY::KEY_C, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_SPACE, KeyEvent::KEY_PRESS);

	Collidable::SetCollidableGroup<PlayerTank>();
	Collidable::SetCollisionModel(m_pHull->getModel(), BSPHERE);
	Collidable::SubmitRegistration();
}

PlayerTank::~PlayerTank()
{
	delete m_pHull;
	delete m_pTurret;
	delete m_pGun;
	delete m_pFollowCam;
	delete m_pStrHealth;
	delete m_pStrEnemyDestroyed;
	delete m_pStrLoss;
	delete m_pStrWin;
}

void PlayerTank::Initialize(Vect& pos)
{
	Matrix rot = Matrix(IDENTITY);
	Matrix trans = Matrix(TRANS, pos);
	Initialize(rot, trans);
}

void PlayerTank::Initialize(Matrix& rot, Matrix& trans)
{
	// hull
	m_tankRotTrans = rot * trans;
	m_pHull->SetWorld(m_tankRotTrans);

	Collidable::UpdateCollisionData(m_tankRotTrans);

	// turret
	m_turretRot = rot;
	Matrix world = Matrix(TRANS, m_turretOffset) * m_tankRotTrans;
	m_pTurret->SetWorld(world);
}

void PlayerTank::Draw3D()
{
	if (m_displayLoss)
	{
		// dumb way of preventing draws after player death while still drawing hud
		return;
	}

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

void PlayerTank::Draw2D()
{
	if (m_displayLoss) 
	{
		// dumb way of preventing draws after player death while still drawing hud
		m_pStrLoss->Render();
		return;
	}
	ScreenLog::Clear();
	ScreenLog::Add("Tank POS:");
	ScreenLog::Add("x: %3.2f", m_tankRotTrans[m12]);
	ScreenLog::Add("y: %3.2f", m_tankRotTrans[m13]);
	ScreenLog::Add("z: %3.2f", m_tankRotTrans[m14]);

	m_pStrHealth->Render();
	if (m_displayDestroyed) m_pStrEnemyDestroyed->Render();
	if (m_displayWin) m_pStrWin->Render();
}

void PlayerTank::Update()
{
	// set up time values for consistent movement
	float delta = TimeManager::GetFrameTime();
	float frameTankTransSpeed = m_tankTransSpeed * delta;
	float frameTankRotSpeed = m_tankRotSpeed * delta;
	float frameTurretRotSpeed = m_turretRotSpeed * delta;


	// tank movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		m_tankRotTrans = Matrix(ROT_Y, (frameTankRotSpeed)) * m_tankRotTrans;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		m_tankRotTrans = Matrix(ROT_Y, -frameTankRotSpeed) * m_tankRotTrans;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		m_tankRotTrans = Matrix(TRANS, Vect(0, 0, frameTankTransSpeed)) * m_tankRotTrans;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		m_tankRotTrans = Matrix(TRANS, Vect(0, 0, -frameTankTransSpeed)) * m_tankRotTrans;
	}

	// Update tank matrix to conform to terrain
	Vect pos = m_tankRotTrans.get(ROW_3);
	Vect n = SceneManager::GetActiveScene().TerrainNormAt(pos);
	float h = SceneManager::GetActiveScene().TerrainHeightAt(pos);
	Vect r = n.cross(m_tankRotTrans.get(ROW_2));
	Vect up = r.cross(n);
	pos[y] = h;
	m_tankRotTrans = Matrix(ROT_ORIENT, up, n) * Matrix(TRANS, pos);

	// keyboard turret movement
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		m_turretRot *= Matrix(ROT_Y, frameTurretRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		m_turretRot *= Matrix(ROT_Y, -frameTurretRotSpeed);
	}
	// mouse turret movement
	int x, y;
	Lemon::getMousePosition(x, y);
	int centerX = Lemon::GetWidth() / 2;
	if (x < centerX / 1.5) m_turretRot *= Matrix(ROT_Y, frameTurretRotSpeed);
	else if (x > centerX * 1.25) m_turretRot *= Matrix(ROT_Y, -frameTurretRotSpeed);


	// update hull position
	Matrix world = m_tankRotTrans;
	m_pHull->SetWorld(world);

	// update hull collision
	UpdateCollisionData(world);

	// Update turret position relative to hull
	world = m_turretRot * Matrix(TRANS, m_turretOffset) * m_tankRotTrans;
	m_pTurret->SetWorld(world);
	
	// update follower cam position relative to tank, and rotate with turret
	Vect vNewLookAt = m_camLookAt * m_turretRot * Matrix(TRANS, m_turretOffset) * m_tankRotTrans; // This moves the cam position relative to tank's position and rotation
	Vect vNewCamPos = m_camOffset * m_turretRot * Matrix(TRANS, m_turretOffset) * m_tankRotTrans; // This moves the look-at point relative to tank's position and rotation
	m_pFollowCam->setOrientAndPosition( Vect(0, 1, 0), vNewLookAt, vNewCamPos);
	m_pFollowCam->updateCamera();

	// update hud elements
	std::string health = "HEALTH: " + std::to_string(m_health);
	m_pStrHealth->Set(FontManager::Get("stencil_36"), health, m_pStrHealthX, m_pStrHealthY);

	// shot predicter line + aim dir update
	// 
	// manually create screen to NDC
	Vect v0 = Vect(2.0f / float(Lemon::GetWidth()), 0.0f, 0.0f, 0.0f);
	Vect v1 = Vect(0.0f, -2.0f / float(Lemon::GetHeight()), 0.0f, 0.0f);
	Vect v2 = Vect(0.0f, 0.0f, 2.0f, 0.0f);
	Vect v3 = Vect(-1.0f, 1.0f, -1.0f, 1.0f);
	Matrix scr2ndc(v0, v1, v2, v3);

	Matrix perspInv = m_pFollowCam->getProjMatrix().getInv();

	Matrix v2w = m_pFollowCam->getViewMatrix().getInv();

	Vect p0(float(x), float(y), 0.0f, 1.0f); // near point
	Vect p1(float(x), float(y), 1.0f, 1.0f); // far point

	// apply inverse matricies
	p0 *= scr2ndc;
	p0 *= perspInv;
	p0 *= v2w;
	p1 *= scr2ndc;
	p1 *= perspInv;
	// homogenous coord. division, only matters for far point here
	p1[X] = p1[X] / p1[W];
	p1[Y] = p1[Y] / p1[W];
	p1[Z] = p1[Z] / p1[W];
	p1[W] = 1.0f;
	p1 *= v2w;

	m_gunPos = m_gunOffset * world;
	Visualizer::ShowSegment(m_gunPos, p1, Colors::WhiteSmoke);

	m_aimDir = p1 - m_gunPos;
	m_aimDir.norm();

	// set gun pos
	world = Matrix(SCALE, m_gunScale, m_gunScale, m_gunScale) * Matrix(ROT_ORIENT, m_aimDir, Vect(0, 1, 0)) * Matrix(TRANS, m_gunPos); // world was turret world
	m_pGun->SetWorld(world);
}

void PlayerTank::KeyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_SPACE :
		// Fire bullet
		//BulletFactory::CreateBullet(m_turretRot * m_turretOffset * m_bulletOffset * m_tankRotTrans);
		BulletFactory::CreateBullet(Matrix(ROT_ORIENT, m_aimDir, Vect(0,1,0)) * Matrix(TRANS, m_gunPos));
		break;
	case AZUL_KEY::KEY_C :
		// Camera toggle
		if (m_followCameraActive) {
			SceneManager::SetActiveCameraToDefault();
			m_followCameraActive = false;
		}
		else {
			SceneManager::SetActiveCamera(m_pFollowCam);
			m_followCameraActive = true;
		}
	}
}

void PlayerTank::Alarm0()
{
	// for short display of enemy destroyed
	m_displayDestroyed = false;
}

void PlayerTank::Alarm1()
{
	LevelTracker::TransitionLevel();
}

void PlayerTank::Collision(EnemyBullet*)
{
	m_health--;
	if (m_health <= 0)
	{
		m_displayLoss = true;
		Updatable::SubmitDeregistration();
		Collidable::SubmitDeregistration();
	}
}

void PlayerTank::Collision(BossBullet*)
{
	m_displayLoss = true;
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();
}

Vect PlayerTank::GetPos()
{
	return m_tankRotTrans.get(ROW_3);
}

void PlayerTank::DisplayEnemyDestroyed()
{
	m_displayDestroyed = true;
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 1.0f);
}

void PlayerTank::DisplayWin()
{
	m_displayWin = true;
}

void PlayerTank::TransitionLevel()
{
	// Passthrough for delay
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_1, 2.0f);
}
