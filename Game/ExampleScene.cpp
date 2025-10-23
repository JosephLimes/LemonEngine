#include "ExampleScene.h"
#include "ExampleCube.h"

void ExampleScene::Initialize()
{
	// create our game objects when the scene is initialized
	myCube1 = new ExampleCube();
	myCube2 = new ExampleCube();

	// note - for the following setup of our game objects I'm using public
	// data members for simplicity's sake, this is obviously bad practice

	// set the initial world matrix for our cubes
	myCube1->myWorldMat = Matrix(TRANS, -9.0f, 0.0f, 0.0f);
	myCube2->myWorldMat = Matrix(TRANS, 9.0f, 0.0f, 0.0f);

	// set the initial velocities for our cubes
	myCube1->myMoveSpeed = 0.05f;
	myCube2->myMoveSpeed = -0.05f;

	// register our game objects to the scene
	myCube1->SubmitEntry();
	myCube2->SubmitEntry();

	// set our cube type for collision against other (registered) cubes
	SetCollisionSelf<ExampleCube>();
}

void ExampleScene::Terminate()
{
	// clean up our game objects when the scene terminates
	delete myCube1;
	delete myCube2;
}