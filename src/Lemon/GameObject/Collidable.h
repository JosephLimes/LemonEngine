#ifndef _Collidable
#define _Collidable

#include "GameObject/RegistrationState.h"
#include "Scene/CollisionManager.h"
#include "Scene/SceneAttorney.h"
#include "../Collision/Volumes/CollisionVolume.h"

class CollisionVolumeBSphere;
class CollideRegistrationCommand;
class CollideDeregistrationCommand;

class Collidable
{
	friend class CollidableAttorney;

public:
	enum Volumes
	{
		BSPHERE,
		AABB,
		OBB
	};

	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator = (const Collidable&) = delete;
	virtual ~Collidable();

private:
	// Registration/deregistration
	RegistrationState				m_registerState;
	CollideRegistrationCommand*		m_pRegisterCommand;
	CollideDeregistrationCommand*	m_pDeregisterCommand;

	// Reference for fast removal from list in CollidableGroup
	CollisionManager::ListRef		m_listRef;

	// Object type ID
	CollisionManager::TypeID		m_typeID;

	// Collision volumes
	CollisionVolume*				m_pCollisionVolume;
	CollisionVolumeBSphere*			m_pBSphere;
	Model*							m_pCollisionModel;

public:
	void							SubmitRegistration();
	void							SubmitDeregistration();

	const CollisionVolume&			GetCollisionVolume() const;
	const CollisionVolumeBSphere&	GetBSphere() const;

	template <typename T>
	void SetCollidableGroup()
	{
		m_typeID = SceneAttorney::GetCollisionManager()->GetTypeID<T>();
	}

	void							SetCollisionModel(Model* pModel, Volumes type);
	void							UpdateCollisionData(const Matrix& matrix);

	virtual void					CollisionTerrain() {}

private:
	void							Register();
	void							Deregister();
};

#endif _Collidable