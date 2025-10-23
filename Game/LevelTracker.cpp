#include "LevelTracker.h"
#include "PlayerTank.h"
#include "Scene/SceneManager.h"
#include "DemoBossScene.h"

LevelTracker* LevelTracker::m_pInstance;

LevelTracker::LevelTracker()
	:	m_pPlayer(nullptr),
		m_numEnemies(3),
		m_onBossLevel(false)
{}

LevelTracker& LevelTracker::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new LevelTracker;
	}
	return *m_pInstance;
}

void LevelTracker::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void LevelTracker::privInitialize(PlayerTank* pPlayer, bool onBossLevel)
{
	m_pPlayer = pPlayer;
	m_onBossLevel = onBossLevel;
	if (onBossLevel) m_numEnemies = 1;
	else m_numEnemies = 3;
}

PlayerTank* LevelTracker::privGetPlayer()
{
	return m_pPlayer;
}

void LevelTracker::privSetPlayer(PlayerTank* pPlayer)
{
	m_pPlayer = pPlayer;
}

void LevelTracker::privEnemyDestroyed()
{
	m_pPlayer->DisplayEnemyDestroyed();
	m_numEnemies--;
	if (m_numEnemies <= 0)
	{
		if (m_onBossLevel)
		{
			m_pPlayer->DisplayWin();
		}
		else
		{
			// passthrough to player to use their alarm...
			m_pPlayer->TransitionLevel();
		}
	}
}

void LevelTracker::privBossDestroyed()
{
	m_pPlayer->DisplayWin();
}

void LevelTracker::privTransitionLevel()
{
	SceneManager::SetNextScene(new DemoBossScene());
}
