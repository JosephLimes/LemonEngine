#ifndef _Bullet
#define _Bullet

#include "GameObject/GameObject.h"

class EnemyTank;
class BossTank;
class BuildingA;
class BuildingB;
class Container;
class WallA;
class WallB;

class Bullet : public GameObject
{
public:
	Bullet();
	Bullet(const Bullet&) = delete;
	Bullet& operator=(const Bullet&) = delete;
	~Bullet();

private:
	GraphicsObject_WireframeConstantColor*	m_pGraphicsObj;
	Matrix									m_rotTrans;
	Matrix									m_scale;
	const float								m_speed = 50.0f;

public:
	void									Initialize(Matrix rotTrans);

	void									Draw3D() override;
	void									Update() override;
	void									Alarm0() override;
	void									SceneExit() override;

	void									Collision(EnemyTank*);
	void									Collision(BossTank*);
	void									Collision(BuildingA*);
	void									Collision(BuildingB*);
	void									Collision(Container*);
	void									Collision(WallA*);
	void									Collision(WallB*);
};

#endif _Bullet