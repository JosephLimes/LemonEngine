#ifndef _Barrel
#define _Barrel

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class Barrel : public LevelObject
{
public:
	Barrel() = default;
	Barrel(const Barrel&) = delete;
	Barrel& operator = (const Barrel&) = delete;
	~Barrel();

	// level object
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
	GraphicsObject_TextureLight*	m_pGraphicsObj;
};

#endif _Barrel