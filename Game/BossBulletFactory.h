#ifndef _BossBulletFactory
#define _BossBulletFactory

#include "AzulCore.h"
#include "BossBulletObjectPool.h"
#include <vector>

class BossBulletFactory
{
private:
	BossBulletFactory() = default;
	BossBulletFactory(const BossBulletFactory&) = delete;
	BossBulletFactory& operator=(const BossBulletFactory&) = delete;
	~BossBulletFactory() = default;

	static BossBulletFactory*					m_pInstance;

	static BossBulletFactory&					Instance();

	BossBulletObjectPool						m_BossBulletPool;
	std::vector<BossBullet*>					m_activeBossBullets;

	void privCreateBossBullet(Vect pos, Vect dir);
	void privRecycleBossBullet(BossBullet* b);
	void privRecall();

public:
	static void CreateBossBullet(Vect pos, Vect dir) { Instance().privCreateBossBullet(pos, dir); };
	static void RecycleBossBullet(BossBullet* b) { Instance().privRecycleBossBullet(b); };
	static void Recall() { Instance().privRecall(); };

	static void Terminate();
};

#endif _BossBulletFactory