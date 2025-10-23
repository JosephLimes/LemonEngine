#ifndef _BuildingA
#define _BuildingA

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class BuildingA : public LevelObject
{
public:
	BuildingA() = default;
	BuildingA(const BuildingA&) = delete;
	BuildingA& operator = (const BuildingA&) = delete;
	~BuildingA();

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
	GraphicsObject_TextureLight*	m_pGraphicsObj;
};

#endif _BuildingA