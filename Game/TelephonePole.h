#ifndef _TelephonePole
#define _TelephonePole

#include "Tools/Editor/LevelObject.h"

class Bullet;
class EnemyBullet;
class BossBullet;
class PlayerTank;
class EnemyTank;

class TelephonePole : public LevelObject
{
public:
	TelephonePole() = default;
	TelephonePole(const TelephonePole&) = delete;
	TelephonePole& operator = (const TelephonePole&) = delete;
	~TelephonePole();

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

#endif _TelephonePole