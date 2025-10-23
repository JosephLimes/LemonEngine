#ifndef _BossBullet
#define _BossBullet

#include "GameObject/GameObject.h"

class PlayerTank;
class Obstacle;

class BossBullet : public GameObject
{
public:
	BossBullet();
	BossBullet(const BossBullet&) = delete;
	BossBullet& operator=(const BossBullet&) = delete;
	~BossBullet();

private:
	//GraphicsObject_WireframeConstantColor*	m_pGraphicsObj;
	GraphicsObject_TextureFlat*				m_pGraphicsObj;
	Matrix									m_rotTrans;
	Matrix									m_scale;
	Vect									m_pos;
	Vect									m_dir;
	const float								m_speed = 25.0f;

public:
	void									Initialize(Vect pos, Vect dir);

	void									Draw3D() override;
	void									Update() override;
	void									Alarm0() override;
	void									SceneExit() override;

	void									Collision(PlayerTank*);
	void									Collision(Obstacle*);
};

#endif _BossBullet