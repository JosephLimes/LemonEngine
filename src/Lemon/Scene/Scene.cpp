#include "Scene.h"
#include "Camera Management/CameraManager.h"
#include "Asset Management/TerrainManager.h"
#include "CollisionManager.h"
#include "Scene/Command/SceneRegistrationBroker.h"
#include "Tools/Editor/MapFileParser.h"
#include "Tools/Editor/LevelObject.h"
#include "Tools/Editor/EditorDrawableManager.h"
#include "Terrain/Terrain.h"

Scene::Scene()
	:	m_pAlarmableMgr(new AlarmableManager),
		m_pDrawableMgr(new DrawableManager), 
		m_pUpdatableMgr(new UpdatableManager),
		m_pKBInputMgr(new KeyboardInputManager),
		m_pMouseInputMgr(new MouseInputManager),
		m_pCollisionMgr(new CollisionManager),
		m_pCameraMgr(new CameraManager),
		m_pTerrainMgr(new SceneTerrainManager),
		m_pRegistrationBrkr(new SceneRegistrationBroker)
{}

Scene::~Scene()
{
	delete m_pAlarmableMgr;
	delete m_pDrawableMgr;
	delete m_pUpdatableMgr;
	delete m_pKBInputMgr;
	delete m_pMouseInputMgr;
	delete m_pCollisionMgr;
	delete m_pCameraMgr;
	delete m_pTerrainMgr;
	delete m_pRegistrationBrkr;

	for (LevelObject* pObj : m_levelObjs)
	{
		delete pObj;
	}
}

void Scene::SubmitCommand(Command* pCmd)
{
	m_pRegistrationBrkr->AddCommand(pCmd);
}

Camera* Scene::GetActiveCamera()
{
	return m_pCameraMgr->GetActiveCamera();
}

void Scene::SetActiveCamera(Camera* pCam)
{
	m_pCameraMgr->SetActiveCamera(pCam);
}

void Scene::SetActiveCameraToDefault()
{
	m_pCameraMgr->SetActiveCameraToDefault();
}

Camera* Scene::GetSpriteCamera()
{
	return m_pCameraMgr->GetSpriteCamera();
}


void Scene::SetInputMode(InputMode mode)
{
	m_pKBInputMgr->SetInputMode(mode);
}

Vect Scene::TerrainNormAt(Vect& pos)
{
	return m_pTerrainMgr->GetTerrain()->NormAt(pos);
}

float Scene::TerrainHeightAt(Vect& pos)
{
	return m_pTerrainMgr->GetTerrain()->HeightAt(pos);
}

void Scene::SetTerrain(std::string id)
{
	m_pTerrainMgr->SetTerrain(TerrainManager::Get(id));
}

void Scene::LevelInitialize(std::string mapname)
{
	MapFileParser::ReadMapFile("../Maps/" + mapname + ".lmf", m_levelObjs);
}

void Scene::Register(float time, Alarmable* pObj, AlarmableManager::AlarmID id, AlarmableManager::ListRef& ref)
{
	m_pAlarmableMgr->Register(time, pObj, id, ref);
}

void Scene::Register(Drawable* pObj, DrawableManager::ListRef& ref)
{
	m_pDrawableMgr->Register(pObj, ref);
}

void Scene::Register(Updatable* pObj, UpdatableManager::ListRef& ref)
{
	m_pUpdatableMgr->Register(pObj, ref);
}

void Scene::Register(Inputable* pObj, AZUL_KEY key, KeyEvent event, KeyboardInputManager::ListRef& ref)
{
	m_pKBInputMgr->Register(pObj, key, event, ref);
}

void Scene::Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event, MouseInputManager::ListRef& ref)
{
	m_pMouseInputMgr->Register(pObj, button, event, ref);
}

void Scene::Deregister(const AlarmableManager::ListRef& ref)
{
	m_pAlarmableMgr->Deregister(ref);
}

void Scene::Deregister(const DrawableManager::ListRef& ref)
{
	m_pDrawableMgr->Deregister(ref);
}

void Scene::Deregister(const UpdatableManager::ListRef& ref)
{
	m_pUpdatableMgr->Deregister(ref);
}

void Scene::Deregister(AZUL_KEY key, KeyEvent event, const KeyboardInputManager::ListRef& ref)
{
	m_pKBInputMgr->Deregister(key, event, ref);
}

void Scene::Deregister(AZUL_MOUSE button, ButtonEvent event, const MouseInputManager::ListRef& ref)
{
	m_pMouseInputMgr->Deregister(button, event, ref);
}

void Scene::Draw()
{
	m_pTerrainMgr->Draw();
	m_pDrawableMgr->ProcessElements();
}

void Scene::Update()
{
	// Handle all pending commands before any other processing
	m_pRegistrationBrkr->ExecuteCommands();

	m_pCollisionMgr->ProcessCollisions();
	m_pUpdatableMgr->ProcessElements();
	m_pKBInputMgr->ProcessElements();
	m_pMouseInputMgr->ProcessElements();
	m_pAlarmableMgr->ProcessElements();
}

void Scene::QueueInput(int key)
{
	m_pKBInputMgr->QueueInput(key);
}

void Scene::RegisterTyped(Inputable* pObj, KeyboardInputManager::ListRef& ref)
{
	m_pKBInputMgr->RegisterTyped(pObj, ref);
}

void Scene::DeregisterTyped(KeyboardInputManager::ListRef& ref)
{
	m_pKBInputMgr->DeregisterTyped(ref);
}

void Scene::EnableEditorMode()
{
	// swap drawable manager with editor version
	delete m_pDrawableMgr;
	m_pDrawableMgr = new EditorDrawableManager();

	// set terrain to wireframe mode
	m_pTerrainMgr->GetTerrain()->ToggleWireframe();
}
