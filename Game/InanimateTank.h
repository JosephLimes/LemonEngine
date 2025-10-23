#ifndef _InanimateTank
#define _InanimateTank

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class InanimateTank : public LevelObject
{
public:
	InanimateTank() = default;
	InanimateTank(const InanimateTank&) = delete;
	InanimateTank& operator = (const InanimateTank&) = delete;
	~InanimateTank();

	// levl object
	DEF_FUNC_LVL_ID
	void							LevelInitialize() override;
	void							LevelTerminate() override;

	void							SceneEntry() override;
	void							SceneExit() override;

	void							Update() override;
	void							Draw3D() override;

	void							Collision(Bullet*);
	void							Collision(EnemyBullet*);
	void							Collision(BossBullet*);
	void							Collision(PlayerTank*);
	void							Collision(EnemyTank*);

private:
	GraphicsObject_TextureLight*	m_pGOhull;
	GraphicsObject_TextureLight*	m_pGOturret;
	GraphicsObject_TextureLight*	m_pGOgun;

	const Vect						m_turretOffset = Vect(0.0f, 135.0f, 45.0f);
	const Vect						m_gunOffset = Vect(0.0f, 151.0f, 95.0f);
};

#endif _InanimateTank