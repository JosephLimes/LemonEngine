#include "BossBulletFactory.h"
#include "BossBulletObjectPool.h"
#include "BossBullet.h"

BossBulletFactory* BossBulletFactory::m_pInstance = nullptr;


BossBulletFactory& BossBulletFactory::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new BossBulletFactory();
	}
	return *m_pInstance;
}

void BossBulletFactory::privCreateBossBullet(Vect pos, Vect dir)
{
	BossBullet* b = m_BossBulletPool.GetBossBullet();

	b->Initialize(pos, dir);
	m_activeBossBullets.push_back(b);
}

void BossBulletFactory::privRecycleBossBullet(BossBullet* b)
{
	m_BossBulletPool.ReturnBossBullet(b);
	m_activeBossBullets.erase(std::remove(m_activeBossBullets.begin(), m_activeBossBullets.end(), b), m_activeBossBullets.end());
}

void BossBulletFactory::privRecall()
{
	for (BossBullet* b : m_activeBossBullets)
	{
		b->SubmitExit();
	}
}

void BossBulletFactory::Terminate()
{
	for (BossBullet* b : Instance().m_activeBossBullets)
	{
		delete b;
	}

	delete m_pInstance;
	m_pInstance = nullptr;
}
