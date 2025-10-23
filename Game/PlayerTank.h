#ifndef _PlayerTank
#define _PlayerTank

#include "GameObject\GameObject.h"

class EnemyBullet;
class BossBullet;
class Camera;
class SpriteString;

class PlayerTank : public GameObject
{
public:
	PlayerTank();
	PlayerTank(const PlayerTank&) = delete;
	PlayerTank& operator = (const PlayerTank&) = delete;
	~PlayerTank();

private:
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
	const float								m_turretRotSpeed = 1.5f;

	const Vect								m_gunOffset = Vect(0.0f, 16.0f, 50.0f); // relative to turret
	Vect									m_gunPos;
	const float								m_gunScale = 2.75f;
	Vect									m_aimDir;

	// Follow camera vars
	bool									m_followCameraActive;
	Camera*									m_pFollowCam;
	const Vect								m_camLookAt = Vect(0, 100, 0);
	const Vect								m_camOffset = Vect(0, 100, -700);

	// HUD strings
	SpriteString*							m_pStrHealth;
	float									m_pStrHealthX;
	float									m_pStrHealthY;
	SpriteString*							m_pStrEnemyDestroyed;
	bool									m_displayDestroyed;
	SpriteString*							m_pStrLoss;
	bool									m_displayLoss;
	SpriteString*							m_pStrWin;
	bool									m_displayWin;

public:
	void									Initialize(Vect& pos);
	void									Initialize(Matrix& rot, Matrix& trans);

	void									Draw3D() override;
	void									Draw2D() override;
	void									Update() override;
	void									KeyPressed(AZUL_KEY key) override;
	void									Alarm0() override;
	void									Alarm1() override;

	void									Collision(EnemyBullet*);
	void									Collision(BossBullet*);

	Vect									GetPos();
	void									DisplayEnemyDestroyed();
	void									DisplayWin();
	void									TransitionLevel();
};

#endif _PlayerTank