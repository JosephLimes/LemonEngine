#include "DemoBossScene.h"

#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

#include "DebugController.h"
#include "BossTank.h"
#include "BossBullet.h"
#include "PlayerTank.h"
#include "Plane.h"
#include "BulletFactory.h"
#include "BossBulletFactory.h"
#include "Bullet.h"
#include "LevelTracker.h"

void DemoBossScene::Initialize()
{
	LevelInitialize("TANK_BOSS");

	m_pPlayerTank = new PlayerTank();
	Vect pos = Vect(0.0f, 0.0f, -6850.0f);
	m_pPlayerTank->Initialize(pos);
	LevelTracker::Initialize(m_pPlayerTank, true);

	m_pBoss = new BossTank();

	SetCollisionPair<BossBullet, PlayerTank>();
	SetCollisionPair<Bullet, BossTank>();
}

void DemoBossScene::Terminate()
{
	LevelTracker::Terminate();
	BulletFactory::Terminate();
	BossBulletFactory::Terminate();

	delete m_pPlayerTank;
	delete m_pBoss;
}