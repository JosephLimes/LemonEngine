#ifndef _DemoBossScene
#define _DemoBossScene

#include "Scene\Scene.h"

class DebugController;
class BossTank;
class PlayerTank;

class DemoBossScene : public Scene
{
public:
	DemoBossScene() = default;
	DemoBossScene(const DemoBossScene&) = delete;
	DemoBossScene& operator = (const DemoBossScene&) = delete;
	~DemoBossScene() = default;

	virtual void			Initialize() override;
	virtual void			Terminate() override;

private:
	PlayerTank*				m_pPlayerTank;
	BossTank*				m_pBoss;
};

#endif _DemoBossScene