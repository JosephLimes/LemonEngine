#include "EnemyBulletObjectPool.h"
#include "EnemyBullet.h"

EnemyBullet* EnemyBulletObjectPool::GetEnemyBullet()
{
	EnemyBullet* b;

	if (recycledItems.empty())
	{
		//Trace::out("Creating EnemyBullet with new.\n");
		b = new EnemyBullet();
	}
	else
	{
		//Trace::out("Recycling EnemyBullet.\n");
		b = recycledItems.top();
		recycledItems.pop();
	}

	return b;
}

void EnemyBulletObjectPool::ReturnEnemyBullet(EnemyBullet* b)
{
	recycledItems.push(b);
}

EnemyBulletObjectPool::~EnemyBulletObjectPool()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}