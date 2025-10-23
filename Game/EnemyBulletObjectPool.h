#ifndef _EnemyBulletObjectPool
#define _EnemyBulletObjectPool

#include <stack>
class EnemyBullet;

class EnemyBulletObjectPool
{
private:
	std::stack<EnemyBullet*> recycledItems;

public:
	EnemyBulletObjectPool() = default;
	EnemyBulletObjectPool(const EnemyBulletObjectPool&) = delete;
	EnemyBulletObjectPool& operator=(const EnemyBulletObjectPool&) = delete;
	~EnemyBulletObjectPool();

	EnemyBullet* GetEnemyBullet();
	void ReturnEnemyBullet(EnemyBullet* b);
};

#endif _EnemyBulletObjectPool