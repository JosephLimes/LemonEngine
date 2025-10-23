#ifndef _Container
#define _Container

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class Container : public LevelObject
{
public:
	Container() = default;
	Container(const Container&) = delete;
	Container& operator = (const Container&) = delete;
	~Container();

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
	GraphicsObject_TextureLight*	m_pGObase;
	GraphicsObject_TextureLight*	m_pGOdoorL;
	GraphicsObject_TextureLight*	m_pGOdoorR;
};

#endif _Container