#ifndef _EnemyBullet
#define _EnemyBullet

#include "GameObject/GameObject.h"

class PlayerTank;
class BossTank;
class BuildingA;
class BuildingB;
class Container;
class WallA;
class WallB;

class EnemyBullet : public GameObject
{
public:
	EnemyBullet();
	EnemyBullet(const EnemyBullet&) = delete;
	EnemyBullet& operator=(const EnemyBullet&) = delete;
	~EnemyBullet();

private:
	GraphicsObject_WireframeConstantColor*	m_pGraphicsObj;
	Matrix									m_rotTrans;
	Matrix									m_scale;
	const float								m_speed = 15.0f;

public:
	void									Initialize(Matrix rotTrans);

	void									Draw3D() override;
	void									Update() override;
	void									Alarm0() override;
	void									SceneExit() override;

	void									Collision(PlayerTank*);
	void									Collision(BossTank*);
	void									Collision(BuildingA*);
	void									Collision(BuildingB*);
	void									Collision(Container*);
	void									Collision(WallA*);
	void									Collision(WallB*);
};

#endif _EnemyBullet