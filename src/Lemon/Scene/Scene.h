#ifndef _Scene
#define _Scene

#include "AzulCore.h"

#include "AlarmableManager.h"
#include "DrawableManager.h"
#include "UpdatableManager.h"
#include "CollisionManager.h"
#include "KeyboardInputManager.h"
#include "MouseInputManager.h"
#include "SceneTerrainManager.h"

class Command;
class SceneRegistrationBroker;
class CameraManager;
class LevelObject;

class Scene
{
public:
	friend class SceneAttorney;

	Scene();
	Scene(const Scene&) = delete;
	Scene& operator = (const Scene&) = delete;
	virtual ~Scene();

private:
	AlarmableManager*			m_pAlarmableMgr;
	DrawableManager*			m_pDrawableMgr;
	UpdatableManager*			m_pUpdatableMgr;
	KeyboardInputManager*		m_pKBInputMgr;
	MouseInputManager*			m_pMouseInputMgr;
	CollisionManager*			m_pCollisionMgr;
	CameraManager*				m_pCameraMgr;
	SceneTerrainManager*		m_pTerrainMgr;
	SceneRegistrationBroker*	m_pRegistrationBrkr;

	// may split into separate object
	std::vector<LevelObject*>	m_levelObjs;

public:
	void						SubmitCommand(Command* pCmd);

	Camera*						GetActiveCamera();
	void						SetActiveCamera(Camera* pCam);
	void						SetActiveCameraToDefault();
	Camera*						GetSpriteCamera();

	void						SetInputMode(InputMode mode);

	Vect						TerrainNormAt(Vect& pos);
	float						TerrainHeightAt(Vect& pos);

protected:
	template< typename T >
	void						SetCollisionSelf()
	{
		m_pCollisionMgr->SetCollisionSelf<T>();
	}

	template< typename T1, typename T2 >
	void						SetCollisionPair()
	{
		m_pCollisionMgr->SetCollisionPair<T1, T2>();
	}

	template< typename T >
	void						SetCollisionTerrain()
	{
		m_pCollisionMgr->SetCollisionTerrain<T>(m_pTerrainMgr->GetTerrain());
	}

	// terrain
	void						SetTerrain(std::string id);

	// optional level load
	void						LevelInitialize(std::string mapname);

private:
	virtual void				Initialize() {};
	virtual void				Terminate() {};

	// Game object registration
	void						Register(float time, Alarmable* pObj, AlarmableManager::AlarmID id, AlarmableManager::ListRef& ref);
	void						Register(Drawable* pObj, DrawableManager::ListRef& ref);
	void						Register(Updatable* pObj, UpdatableManager::ListRef& ref);
	void						Register(Inputable* pObj, AZUL_KEY key, KeyEvent event, KeyboardInputManager::ListRef& ref);
	void						Register(Inputable* pObj, AZUL_MOUSE button, ButtonEvent event, MouseInputManager::ListRef& ref);
	void						Deregister(const AlarmableManager::ListRef& ref);
	void						Deregister(const DrawableManager::ListRef& ref);
	void						Deregister(const UpdatableManager::ListRef& ref);
	void						Deregister(AZUL_KEY key, KeyEvent event, const KeyboardInputManager::ListRef& ref);
	void						Deregister(AZUL_MOUSE button, ButtonEvent event, const MouseInputManager::ListRef& ref);

	// Game loop
	void						Draw();
	void						Update();

	// for typed inputs
	void						QueueInput(int key);
	void						RegisterTyped(Inputable* pObj, KeyboardInputManager::ListRef& ref);
	void						DeregisterTyped(KeyboardInputManager::ListRef& ref);

	// for the editor scene
	void						EnableEditorMode();
};

#endif _Scene