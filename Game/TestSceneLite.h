#ifndef _TestSceneLite
#define _TestSceneLite

#include "Scene\Scene.h"

class Frigate;
//class Axis;
//class Plane;

class TestSceneLite : public Scene
{
public:
	TestSceneLite() = default;
	TestSceneLite(const TestSceneLite&) = delete;
	TestSceneLite& operator = (const TestSceneLite&) = delete;
	~TestSceneLite() = default;

	virtual void			Initialize() override;
	virtual void			Terminate() override;
private:
	Frigate*				m_pFrigate;
	//Axis*					m_pAxis;
	//Plane*				m_pPlane;
};

#endif _TestSceneLite