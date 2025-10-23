#ifndef _BulletObjectPool
#define _BulletObjectPool

#include <stack>
class Bullet;

class BulletObjectPool
{
private:
	std::stack<Bullet*> recycledItems;

public:
	BulletObjectPool() = default;
	BulletObjectPool(const BulletObjectPool&) = delete;
	BulletObjectPool& operator=(const BulletObjectPool&) = delete;
	~BulletObjectPool();

	Bullet* GetBullet();
	void ReturnBullet(Bullet* b);
};

#endif _BulletObjectPool