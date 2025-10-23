#include "LevelObjectManager.h"

LevelObjectManager* LevelObjectManager::m_pInstance;

LevelObjectManager::LevelObjectManager()
	: m_selected(nullptr)
{}

LevelObjectManager::~LevelObjectManager()
{
	for (auto entry : m_typeMap)
	{
		delete entry.second;
	}
}

LevelObjectManager& LevelObjectManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new LevelObjectManager;
	}
	return *m_pInstance;
}

void LevelObjectManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

LevelObject* LevelObjectManager::privGet(LevelTypeID ID)
{
	if (m_typeMap.find(ID) != m_typeMap.end())
	{
		return m_typeMap.find(ID)->second->Create();
	}

	// ID not found
	Trace::out("Level object with type ID %zu does not exist.\n", ID);
	assert(nullptr);
	return nullptr;
}

LevelObjectBaseFactory* LevelObjectManager::privGetSelectedFactory()
{
	return m_selected;
}

void LevelObjectManager::privDecrementSelected()
{
	if (m_selectedIt != m_typeMap.begin())
	{
		m_selectedIt--;
		m_selected = m_selectedIt->second;
	}
}

void LevelObjectManager::privIncrementSelected()
{
	if (std::next(m_selectedIt) != m_typeMap.end())
	{
		m_selectedIt++;
		m_selected = m_selectedIt->second;
	}
}
