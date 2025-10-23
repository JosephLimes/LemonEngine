#ifndef _BossBulletObjectPool
#define _BossBulletObjectPool

#include <stack>
class BossBullet;

class BossBulletObjectPool
{
private:
	std::stack<BossBullet*> recycledItems;

public:
	BossBulletObjectPool() = default;
	BossBulletObjectPool(const BossBulletObjectPool&) = delete;
	BossBulletObjectPool& operator=(const BossBulletObjectPool&) = delete;
	~BossBulletObjectPool();

	BossBullet* GetBossBullet();
	void ReturnBossBullet(BossBullet* b);
};

#endif _BossBulletObjectPool