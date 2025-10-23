#include "DemoStartScene.h"

#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

#include "DebugController.h"
#include "EnemyTank.h"
#include "EnemyBullet.h"
#include "PlayerTank.h"
#include "Plane.h"
#include "BulletFactory.h"
#include "EnemyBulletFactory.h"
#include "Bullet.h"
#include "LevelTracker.h"

#include "BuildingA.h"
#include "BuildingB.h"
#include "Container.h"
#include "WallA.h"
#include "WallB.h"

void DemoStartScene::Initialize()
{
	LevelInitialize("TANK_START");

	m_pPlayerTank = new PlayerTank();
	LevelTracker::Initialize(m_pPlayerTank, false);

	m_pEnemy1 = new EnemyTank();
	Vect pos = Vect(-1526, 0, 4421);
	m_pEnemy1->Initialize(pos);

	m_pEnemy2 = new EnemyTank();
	pos = Vect(4335, 0, 1222);
	m_pEnemy2->Initialize(pos);

	m_pEnemy3 = new EnemyTank();
	pos = Vect(-3691, 0, -4503);
	m_pEnemy3->Initialize(pos);

	// bullet -> tank
	SetCollisionPair<EnemyBullet, PlayerTank>();
	SetCollisionPair<Bullet, EnemyTank>();

	// bullet -> prop
	SetCollisionPair<Bullet, BuildingA>();
	SetCollisionPair<Bullet, BuildingB>();
	SetCollisionPair<Bullet, Container>();
	SetCollisionPair<Bullet, WallA>();
	SetCollisionPair<Bullet, WallB>();
	SetCollisionPair<EnemyBullet, BuildingA>();
	SetCollisionPair<EnemyBullet, BuildingB>();
	SetCollisionPair<EnemyBullet, Container>();
	SetCollisionPair<EnemyBullet, WallA>();
	SetCollisionPair<EnemyBullet, WallB>();
}

void DemoStartScene::Terminate()
{
	LevelTracker::Terminate();
	BulletFactory::Terminate();
	EnemyBulletFactory::Terminate();

	delete m_pPlayerTank;
	delete m_pEnemy1;
	delete m_pEnemy2;
	delete m_pEnemy3;
}