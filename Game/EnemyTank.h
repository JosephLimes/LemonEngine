#ifndef _EnemyTank
#define _EnemyTank

#include "GameObject\GameObject.h"

class Bullet;
class Camera;

class EnemyTank : public GameObject
{
public:
	EnemyTank();
	EnemyTank(const EnemyTank&) = delete;
	EnemyTank& operator = (const EnemyTank&) = delete;
	~EnemyTank();
	
private:
	enum MOVEMENT_STATE
	{
		NOT_MOVING,
		MOVE_FORWARD,
		MOVE_BACK,
		TURN_LEFT,
		TURN_RIGHT
	};

	MOVEMENT_STATE							m_moveState;

	int										m_health;
	bool									m_colliding;
	// Tank vars
	GraphicsObject_TextureLight*			m_pHull;
	GraphicsObject_TextureLight*			m_pTurret;
	GraphicsObject_TextureLight*			m_pGun;

	Matrix									m_turretRot;
	const Vect								m_turretOffset = Vect(0.0f, 135.0f, 45.0f); // relative to hull

	Matrix									m_tankRotTrans;

	const float								m_tankTransSpeed = 500.0f;
	const float								m_tankRotSpeed = 1.5f;
	const float								m_turretRotSpeed = 1.75f;

	Matrix									m_gunRot;
	const Vect								m_gunOffset = Vect(0.0f, 16.0f, 50.0f); // relative to turret
	Vect									m_gunPos;
	Vect									m_aimDir;

public:
	void									Draw3D() override;
	void									Update() override;
	void									Alarm0() override;
	void									Alarm1() override;

	void									Collision(Bullet*);

	void									Initialize(Vect& pos);
	void									Initialize(Matrix& rot, Matrix& trans);
};

#endif _EnemyTank