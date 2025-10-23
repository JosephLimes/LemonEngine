#ifndef _Rock5
#define _Rock5

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class Rock5 : public LevelObject
{
public:
	Rock5() = default;
	Rock5(const Rock5&) = delete;
	Rock5& operator = (const Rock5&) = delete;
	~Rock5();

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

#endif _Rock5