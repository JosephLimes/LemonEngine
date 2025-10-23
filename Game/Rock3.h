#ifndef _Rock3
#define _Rock3

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class Rock3 : public LevelObject
{
public:
	Rock3() = default;
	Rock3(const Rock3&) = delete;
	Rock3& operator = (const Rock3&) = delete;
	~Rock3();

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

#endif _Rock3