#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"
#include "SceneManager.h"
#include "AlarmableManager.h"
#include "DrawableManager.h"
#include "UpdatableManager.h"
#include "KeyboardInputManager.h"
#include "MouseInputManager.h"
#include "CollisionManager.h"

class SceneAttorney
{
public:
	friend class SceneManager;
	friend class Alarmable;
	friend class Drawable;
	friend class Updatable;
	friend class Inputable;
	friend class Collidable;
	friend class EditorScene;
	friend class MapFileParser;

	SceneAttorney() = delete;
	SceneAttorney(const SceneAttorney&) = delete;
	SceneAttorney& operator = (const SceneAttorney&) = delete;
	~SceneAttorney() = delete;

private:
	// passthroughs for scene manager
	static void					Initialize(Scene* pScene) { pScene->Initialize(); }
	static void					Terminate(Scene* pScene) { pScene->Terminate(); }
	static void					Update(Scene* pScene) { pScene->Update(); };
	static void					Draw(Scene* pScene) { pScene->Draw(); };
	static void					QueueInput(Scene* pScene, int key) { pScene->QueueInput(key); }
	static void					SetActiveTerrain(Scene* pScene, std::string id) { pScene->SetTerrain(id); }

	// passthroughs for alarmable
	static void					Register(float time, Alarmable* pObj, AlarmableManager::AlarmID id, AlarmableManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Register(time, pObj, id, listRef);
	};
	static void					Deregister(const AlarmableManager::ListRef& listRef) { SceneManager::GetActiveScene().Deregister(listRef); };

	// passthroughs for drawable
	static void					Register(Drawable* pObj, DrawableManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Register(pObj, listRef);
	};
	static void					Deregister(const DrawableManager::ListRef& listRef) { SceneManager::GetActiveScene().Deregister(listRef); };

	// passthroughs for updatable
	static void					Register(Updatable* pObj, UpdatableManager::ListRef& listRef) { SceneManager::GetActiveScene().Register(pObj, listRef); };
	static void					Deregister(const UpdatableManager::ListRef& listRef) { SceneManager::GetActiveScene().Deregister(listRef); };

	// passthroughs for inputable
	static void					Register(Inputable* pObj, AZUL_KEY key, KeyEvent event, KeyboardInputManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Register(pObj, key, event, listRef);
	};
	static void					Deregister(AZUL_KEY key, KeyEvent event, const KeyboardInputManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Deregister(key, event, listRef);
	};
	static void					RegisterTyped(Inputable* pObj, KeyboardInputManager::ListRef& listRef) { SceneManager::GetActiveScene().RegisterTyped(pObj, listRef); }
	static void					DeregisterTyped(KeyboardInputManager::ListRef& listRef) { SceneManager::GetActiveScene().DeregisterTyped(listRef); }
	static void					Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event, MouseInputManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Register(pObj, button, event, listRef);
	};
	static void					Deregister(AZUL_MOUSE button, ButtonEvent event, const MouseInputManager::ListRef& listRef)
	{
		SceneManager::GetActiveScene().Deregister(button, event, listRef);
	};

	// passthroughs for collidable
	static CollisionManager*	GetCollisionManager() { return SceneManager::GetActiveScene().m_pCollisionMgr; }

	// passthrough for editor
	static void					EnableEditorMode() { SceneManager::GetActiveScene().EnableEditorMode(); }
	static void					SetTerrain(std::string id) { SceneManager::GetActiveScene().SetTerrain(id); }
};

#endif _SceneAttorney