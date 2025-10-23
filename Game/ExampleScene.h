#ifndef _ExampleScene
#define _ExampleScene

#include "Scene/Scene.h"

// forward declaration of our game object
class ExampleCube;

class ExampleScene : public Scene
{
	void Initialize() override;
	void Terminate() override;

	ExampleCube* myCube1;
	ExampleCube* myCube2;
};

#endif _ExampleScene