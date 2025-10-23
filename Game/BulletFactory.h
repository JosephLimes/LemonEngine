#ifndef _BulletFactory
#define _BulletFactory

#include "AzulCore.h"
#include "BulletObjectPool.h"
#include <vector>

class BulletFactory
{
private:
	BulletFactory() = default;
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory() = default;

	static BulletFactory*					m_pInstance;

	static BulletFactory&					Instance();

	BulletObjectPool						m_bulletPool;
	std::vector<Bullet*>					m_activeBullets;

	void privCreateBullet(Matrix rotTrans);
	void privRecycleBullet(Bullet* b);
	void privRecall();

public:
	static void CreateBullet(Matrix rotTrans) { Instance().privCreateBullet(rotTrans); };
	static void RecycleBullet(Bullet* b) { Instance().privRecycleBullet(b); };
	static void Recall() { Instance().privRecall(); };

	static void Terminate();
};

#endif _BulletFactory