#include "Collidable.h"
#include "Scene/Command/CollideRegistrationCommand.h"
#include "Scene/Command/CollideDeregistrationCommand.h"
#include "Collision/CollidableGroup.h"
#include "Collision/Volumes/CollisionVolumeBSphere.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Collision/Volumes/CollisionVolumeOBB.h"

Collidable::Collidable()
	:	m_registerState(RegistrationState::CURRENTLY_DEREGISTERED),
		m_pRegisterCommand(new CollideRegistrationCommand(this)),
		m_pDeregisterCommand(new CollideDeregistrationCommand(this)),
		m_typeID(SceneAttorney::GetCollisionManager()->ID_UNDEFINED),
		m_pCollisionVolume(nullptr),
		m_pBSphere(new CollisionVolumeBSphere()),
		m_pCollisionModel(nullptr)
{}

Collidable::~Collidable()
{
	delete m_pRegisterCommand;
	delete m_pDeregisterCommand;
	delete m_pCollisionVolume;
	delete m_pBSphere;
}

void Collidable::SubmitRegistration()
{
	// Submit a collision registration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_DEREGISTERED);
	m_registerState = RegistrationState::PENDING_REGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pRegisterCommand);
}

void Collidable::SubmitDeregistration()
{
	// Submit a collision deregistration request to the scene

	assert(m_registerState == RegistrationState::CURRENTLY_REGISTERED);
	m_registerState = RegistrationState::PENDING_DEREGISTRATION;
	SceneManager::GetActiveScene().SubmitCommand(m_pDeregisterCommand);
}

const CollisionVolume& Collidable::GetCollisionVolume() const
{
	return *m_pCollisionVolume;
}

const CollisionVolumeBSphere& Collidable::GetBSphere() const
{
	return *m_pBSphere;
}

void Collidable::SetCollisionModel(Model* pModel, Volumes type)
{
	m_pCollisionModel = pModel;

	switch (type)
	{
	case BSPHERE:
		m_pCollisionVolume = new CollisionVolumeBSphere();
		break;
	case AABB:
		m_pCollisionVolume = new CollisionVolumeAABB();
		break;
	case OBB:
		m_pCollisionVolume = new CollisionVolumeOBB();
		break;
	}
}

void Collidable::UpdateCollisionData(const Matrix& matrix)
{
	m_pCollisionVolume->ComputeData(this->m_pCollisionModel, matrix);
	m_pBSphere->ComputeData(this->m_pCollisionModel, matrix);
}

void Collidable::Register()
{
	// Register to scene (called from commands sent to scene)

	assert(m_registerState == RegistrationState::PENDING_REGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_REGISTERED;
	
	SceneAttorney::GetCollisionManager()->GetColGroup(m_typeID)->Register(this, m_listRef);

	//DebugMsg::out("Collidable registered.\n");
}

void Collidable::Deregister()
{
	// Deregister from scene (called from commands sent to scene)

	assert(m_registerState == RegistrationState::PENDING_DEREGISTRATION);
	m_registerState = RegistrationState::CURRENTLY_DEREGISTERED;
	
	SceneAttorney::GetCollisionManager()->GetColGroup(m_typeID)->Deregister(m_listRef);

	//DebugMsg::out("Collidable deregistered.\n");
}

