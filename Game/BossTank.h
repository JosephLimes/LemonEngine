#ifndef _BossTank
#define _BossTank

#include "GameObject\GameObject.h"

class Bullet;
class Camera;
class Sprite;

class BossTank : public GameObject
{
public:
	BossTank();
	BossTank(const BossTank&) = delete;
	BossTank& operator = (const BossTank&) = delete;
	~BossTank();
	
private:
	const int								m_maxHealth = 50;
	int										m_health;
	bool									m_colliding;

	Sprite*									m_pHealthbar;

	// Tank vars
	GraphicsObject_TextureLight*			m_pHull;
	GraphicsObject_TextureLight*			m_pTurret;
	GraphicsObject_TextureLight*			m_pGun;

	Matrix									m_turretRot;
	const Vect								m_turretOffset = Vect(0.0f, 945.0f, 315.0f); // relative to hull

	const Matrix							m_tankScale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	Matrix									m_tankRotTrans;

	const float								m_tankTransSpeed = 50.0f;
	const float								m_tankRotSpeed = 1.5f;
	const float								m_turretRotSpeed = 1.75f;

	const Vect								m_gunOffset = Vect(0.0f, 112.0f, 350.0f); // relative to turret
	Vect									m_gunPos;
	
	const int								m_volleyTotal = 20;
	int										m_volleyFired;
	void									StartVolley();
	void									EndVolley();

public:
	void									Draw2D() override;
	void									Draw3D() override;
	void									Update() override;
	void									Alarm0() override; // attack
	void									Alarm1() override; // fire volley up
	void									Alarm2() override; // fire volley down

	void									Collision(Bullet*);

	void									Initialize(Vect& pos);
	void									Initialize(Matrix& rot, Matrix& trans);
};

#endif _BossTank