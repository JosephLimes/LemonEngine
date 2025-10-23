#include "BossBulletObjectPool.h"
#include "BossBullet.h"

BossBullet* BossBulletObjectPool::GetBossBullet()
{
	BossBullet* b;

	if (recycledItems.empty())
	{
		//Trace::out("Creating BossBullet with new.\n");
		b = new BossBullet();
	}
	else
	{
		//Trace::out("Recycling BossBullet.\n");
		b = recycledItems.top();
		recycledItems.pop();
	}

	return b;
}

void BossBulletObjectPool::ReturnBossBullet(BossBullet* b)
{
	recycledItems.push(b);
}

BossBulletObjectPool::~BossBulletObjectPool()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}