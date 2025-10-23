#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
	friend class Lemon;
	friend class SceneChangeActive;

	SceneManagerAttorney() = delete;
	SceneManagerAttorney(const SceneManagerAttorney&) = delete;
	SceneManagerAttorney& operator = (const SceneManagerAttorney&) = delete;
	~SceneManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { SceneManager::Terminate(); }
	static void			Update() { SceneManager::Update(); }
	static void			Draw() { SceneManager::Draw(); }
	static void			QueueInput(int key) { SceneManager::QueueInput(key); }
	// passthrough for scene change strategy
	static void			ChangeScene(Scene* pScene) { SceneManager::ChangeScene(pScene); }
};

#endif _SceneManagerAttorney