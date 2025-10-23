#include "EnemyBulletFactory.h"
#include "EnemyBulletObjectPool.h"
#include "EnemyBullet.h"

EnemyBulletFactory* EnemyBulletFactory::m_pInstance = nullptr;


EnemyBulletFactory& EnemyBulletFactory::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new EnemyBulletFactory();
	}
	return *m_pInstance;
}

void EnemyBulletFactory::privCreateEnemyBullet(Matrix rotTrans)
{
	EnemyBullet* b = m_EnemyBulletPool.GetEnemyBullet();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	//b->SetExternalManagement(RecycleEnemyBullet);

	b->Initialize(rotTrans);
	m_activeEnemyBullets.push_back(b);
}

void EnemyBulletFactory::privRecycleEnemyBullet(EnemyBullet* b)
{
	m_EnemyBulletPool.ReturnEnemyBullet(b);
	m_activeEnemyBullets.erase(std::remove(m_activeEnemyBullets.begin(), m_activeEnemyBullets.end(), b), m_activeEnemyBullets.end());
}

void EnemyBulletFactory::privRecall()
{
	for (EnemyBullet* b : m_activeEnemyBullets)
	{
		b->SubmitExit();
	}
}

void EnemyBulletFactory::Terminate()
{
	for (EnemyBullet* b : Instance().m_activeEnemyBullets)
	{
		delete b;
	}

	delete m_pInstance;
	m_pInstance = nullptr;
}
