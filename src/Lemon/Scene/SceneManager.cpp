#include "SceneManager.h"
#include "Scene.h"
#include "SceneAttorney.h"
#include "SceneNull.h"
#include "SceneChangeNull.h"
#include "SceneChangeActive.h"

SceneManager* SceneManager::m_pInstance;

SceneManager::SceneManager()
	:	m_pActiveScene(new SceneNull()),
		m_pSceneChangeNull(new SceneChangeNull()),
		m_pSceneChangeActive(new SceneChangeActive()),
		m_pSceneChange(m_pSceneChangeNull)
{}

SceneManager::~SceneManager()
{
	// clean up scene
	SceneAttorney::Terminate(m_pActiveScene);
	delete m_pActiveScene;

	// clean up strategies
	delete m_pSceneChangeNull;
	delete m_pSceneChangeActive;
}

SceneManager& SceneManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SceneManager;
	}
	return *m_pInstance;
}

Scene& SceneManager::privGetActiveScene()
{
	return *m_pActiveScene;
}

void SceneManager::privSetNextScene(Scene* pScene)
{
	assert(m_pSceneChange == m_pSceneChangeNull); // make sure a scene change is not already pending

	m_pSceneChangeActive->SetScene(pScene);
	m_pSceneChange = m_pSceneChangeActive;
}

void SceneManager::ChangeScene(Scene* pScene)
{
	SceneManager& mgr = Instance();

	// close out current scene
	SceneAttorney::Terminate(mgr.m_pActiveScene);
	delete mgr.m_pActiveScene;

	// set up new scene
	mgr.m_pActiveScene = pScene;
	SceneAttorney::Initialize(mgr.m_pActiveScene);

	// reset change strategy
	mgr.m_pSceneChange = mgr.m_pSceneChangeNull;
}

void SceneManager::Update()
{
	SceneManager& instance = SceneManager::Instance();

	// change scene if pending
	instance.m_pSceneChange->Process();

	// update scene
	SceneAttorney::Update(instance.m_pActiveScene);
}

void SceneManager::Draw()
{
	SceneAttorney::Draw(SceneManager::Instance().m_pActiveScene);
}

Camera* SceneManager::privGetActiveCamera()
{
	return m_pActiveScene->GetActiveCamera();
}

void SceneManager::privSetActiveCamera(Camera* pCam)
{
	m_pActiveScene->SetActiveCamera(pCam);
}

void SceneManager::privSetActiveCameraToDefault()
{
	m_pActiveScene->SetActiveCameraToDefault();
}

Camera* SceneManager::privGetSpriteCamera()
{
	return m_pActiveScene->GetSpriteCamera();
}

void SceneManager::Terminate()
{
	// delete manager instance
	delete m_pInstance;
	m_pInstance = nullptr;
}

void SceneManager::privSetInputMode(InputMode mode)
{
	m_pActiveScene->SetInputMode(mode);
}

void SceneManager::QueueInput(int key)
{
	SceneAttorney::QueueInput(Instance().m_pActiveScene, key);
}

void SceneManager::privSetActiveTerrain(std::string id)
{
	SceneAttorney::SetActiveTerrain(m_pActiveScene, id);
}
