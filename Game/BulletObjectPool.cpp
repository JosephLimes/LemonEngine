#include "BulletObjectPool.h"
#include "Bullet.h"

Bullet* BulletObjectPool::GetBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{
		//Trace::out("Creating bullet with new.\n");
		b = new Bullet();
	}
	else
	{
		//Trace::out("Recycling bullet.\n");
		b = recycledItems.top();
		recycledItems.pop();
	}

	return b;
}

void BulletObjectPool::ReturnBullet(Bullet* b)
{
	recycledItems.push(b);
}

BulletObjectPool::~BulletObjectPool()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}