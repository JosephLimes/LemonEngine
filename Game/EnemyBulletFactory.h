#ifndef _EnemyBulletFactory
#define _EnemyBulletFactory

#include "AzulCore.h"
#include "EnemyBulletObjectPool.h"
#include <vector>

class EnemyBulletFactory
{
private:
	EnemyBulletFactory() = default;
	EnemyBulletFactory(const EnemyBulletFactory&) = delete;
	EnemyBulletFactory& operator=(const EnemyBulletFactory&) = delete;
	~EnemyBulletFactory() = default;

	static EnemyBulletFactory*					m_pInstance;

	static EnemyBulletFactory&					Instance();

	EnemyBulletObjectPool						m_EnemyBulletPool;
	std::vector<EnemyBullet*>					m_activeEnemyBullets;

	void privCreateEnemyBullet(Matrix rotTrans);
	void privRecycleEnemyBullet(EnemyBullet* b);
	void privRecall();

public:
	static void CreateEnemyBullet(Matrix rotTrans) { Instance().privCreateEnemyBullet(rotTrans); };
	static void RecycleEnemyBullet(EnemyBullet* b) { Instance().privRecycleEnemyBullet(b); };
	static void Recall() { Instance().privRecall(); };

	static void Terminate();
};

#endif _EnemyBulletFactory