#include "UpdatableManager.h"
#include "GameObject/Updatable.h"
#include "GameObject/UpdatableAttorney.h"

void UpdatableManager::Register(Updatable* pUpdatable, ListRef& ref)
{
	ref = m_registeredObjs.insert(m_registeredObjs.end(), pUpdatable);
}

void UpdatableManager::Deregister(const ListRef& ref)
{
	m_registeredObjs.erase(ref);
}

void UpdatableManager::ProcessElements()
{
	for (Updatable* pObj : m_registeredObjs)
	{
		UpdatableAttorney::GameLoop::Update(pObj);
	}
}
