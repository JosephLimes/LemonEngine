#ifndef _Rock1
#define _Rock1

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class Rock1 : public LevelObject
{
public:
	Rock1() = default;
	Rock1(const Rock1&) = delete;
	Rock1& operator = (const Rock1&) = delete;
	~Rock1();

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
	GraphicsObject_TextureLight* m_pGraphicsObj;
};

#endif _Rock1