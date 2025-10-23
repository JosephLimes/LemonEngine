#ifndef _SceneManager
#define _SceneManager

#include "AzulCore.h"

#include "GameObject/InputTypes.h"

class Scene;
class SceneChange;
class SceneChangeActive;
class Terrain;

class SceneManager
{
private:
	friend class SceneManagerAttorney;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator = (const SceneManager&) = delete;
	~SceneManager();

	static SceneManager*			m_pInstance;
	Scene*							m_pActiveScene;
	SceneChange*					m_pSceneChangeNull;
	SceneChangeActive*				m_pSceneChangeActive;
	SceneChange*					m_pSceneChange;

	static SceneManager&			Instance();

public:
	static Scene&					GetActiveScene() { return Instance().privGetActiveScene(); };
	static void						SetNextScene(Scene* pScene) { Instance().privSetNextScene(pScene); }

	static Camera*					GetActiveCamera() { return Instance().privGetActiveCamera(); }
	static void						SetActiveCamera(Camera* pCam) { Instance().privSetActiveCamera(pCam); }
	static void						SetActiveCameraToDefault() { Instance().privSetActiveCameraToDefault(); }
	static Camera*					GetSpriteCamera() { return Instance().privGetSpriteCamera(); }

	static void						SetInputMode(InputMode mode) { Instance().privSetInputMode(mode); }

	static void						SetActiveTerrain(std::string id) { Instance().privSetActiveTerrain(id); }

private:
	static void						Terminate();

	Scene&							privGetActiveScene();
	void							privSetNextScene(Scene* pScene);
	static void						ChangeScene(Scene* pScene);

	static void						Update();
	static void						Draw();

	Camera*							privGetActiveCamera();
	void							privSetActiveCamera(Camera* pCam);
	void							privSetActiveCameraToDefault();
	Camera*							privGetSpriteCamera();

	void							privSetInputMode(InputMode mode);
	static void						QueueInput(int key);

	void							privSetActiveTerrain(std::string id);
};

#endif _SceneManager