#include "TestSceneLite.h"
#include "Frigate.h"
//#include "Axis.h"
//#include "Plane.h"

void TestSceneLite::Initialize()
{
	m_pFrigate = new Frigate();
	//m_pAxis = new Axis();
	//m_pPlane = new Plane();
}

void TestSceneLite::Terminate()
{
	delete m_pFrigate;
	//zdelete m_pAxis;
	//zdelete m_pPlane;
}