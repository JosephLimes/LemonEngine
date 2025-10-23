#ifndef _DemoStartScene
#define _DemoStartScene

#include "Scene\Scene.h"

class DebugController;
class EnemyTank;
class PlayerTank;
class Ground;
class Obstacle;
class BorderProp;

class DemoStartScene : public Scene
{
public:
	DemoStartScene() = default;
	DemoStartScene(const DemoStartScene&) = delete;
	DemoStartScene& operator = (const DemoStartScene&) = delete;
	~DemoStartScene() = default;

	virtual void			Initialize() override;
	virtual void			Terminate() override;

private:
	PlayerTank*				m_pPlayerTank;
	EnemyTank*				m_pEnemy1;
	EnemyTank*				m_pEnemy2;
	EnemyTank*				m_pEnemy3;
};

#endif _DemoStartScene