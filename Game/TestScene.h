#ifndef _TestScene
#define _TestScene

#include "Scene\Scene.h"

class Frigate;
class Axis;
class Plane;
class DebugController;
class GodCam;
class Terrain;

class TestScene : public Scene
{
public:
	TestScene() = default;
	TestScene(const TestScene&) = delete;
	TestScene& operator = (const TestScene&) = delete;
	~TestScene() = default;

private:
	Frigate*				m_pFrigate;
	Plane*					m_pPlane;
	DebugController*		m_pDebugController;
	GodCam*					m_pGodCam;

	virtual void			Initialize() override;
	virtual void			Terminate() override;
};

#endif _TestScene