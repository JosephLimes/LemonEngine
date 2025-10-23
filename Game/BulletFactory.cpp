#include "BulletFactory.h"
#include "BulletObjectPool.h"
#include "Bullet.h"

BulletFactory* BulletFactory::m_pInstance = nullptr;


BulletFactory& BulletFactory::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new BulletFactory();
	}
	return *m_pInstance;
}

void BulletFactory::privCreateBullet(Matrix rotTrans)
{
	Bullet* b = m_bulletPool.GetBullet();

	// Declares that this object should be returned here (rather than deleted) when destroyed
	//b->SetExternalManagement(RecycleBullet);

	b->Initialize(rotTrans);
	m_activeBullets.push_back(b);
}

void BulletFactory::privRecycleBullet(Bullet* b)
{
	m_bulletPool.ReturnBullet(b);
	m_activeBullets.erase(std::remove(m_activeBullets.begin(), m_activeBullets.end(), b), m_activeBullets.end());
}

void BulletFactory::privRecall()
{
	for (Bullet* b : m_activeBullets)
	{
		b->SubmitExit();
	}
}

void BulletFactory::Terminate()
{
	for (Bullet* b : Instance().m_activeBullets)
	{
		delete b;
	}

	delete m_pInstance;
	m_pInstance = nullptr;
}
