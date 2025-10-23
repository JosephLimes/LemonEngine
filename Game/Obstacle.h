#ifndef _Obstacle
#define _Obstacle

#include "GameObject\GameObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;

class Obstacle : public GameObject
{
public:
	Obstacle(GraphicsObject_TextureFlat* pGO, Matrix& world);
	Obstacle() = delete;
	Obstacle(const Obstacle&) = delete;
	Obstacle& operator = (const Obstacle&) = delete;
	~Obstacle();

	void							Draw3D() override;
	void							Collision(Bullet*);
	void							Collision(EnemyBullet*);
	void							Collision(BossBullet*);
private:
	GraphicsObject_TextureFlat*		m_pGraphicsObj;
};

#endif _Obstacle