#include "TestScene.h"
#include "Frigate.h"
#include "Axis.h"
#include "Plane.h"
#include "GodCam.h"
#include "DebugController.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"
#include "Tools/Colors.h"
#include "Terrain/Terrain.h"
#include "Obstacle.h"
#include "Asset Management/TerrainManager.h"

void TestScene::Initialize()
{
	LevelInitialize("default");

	//InitTestProps();

	//Matrix world = Matrix(TRANS, 0, 20, 100);
	Matrix world = Matrix(IDENTITY);
	m_pFrigate = new Frigate();
	m_pFrigate->LevelInitialize();

	m_pFrigate->SetWorld(world);
	m_pFrigate->SetActive(true);
	m_pFrigate->pTerrain = TerrainManager::Get("64");
	//m_pAxis = new Axis();
	m_pDebugController = new DebugController();
	m_pGodCam = new GodCam();

	//SetTerrain("desert");
	//SetTerrain("64");
	

	SetCollisionPair<Frigate, Axis>();
	SetCollisionTerrain<Frigate>();
}

void TestScene::Terminate()
{
	delete m_pFrigate;
	//delete m_pAxis;
	delete m_pDebugController;
	delete m_pGodCam;
}