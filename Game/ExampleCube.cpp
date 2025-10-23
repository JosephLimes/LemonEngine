#include "ExampleCube.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/TextureManager.h"

ExampleCube::ExampleCube()
{
	// set up our graphics object using assets provided by default in engine
	myGraphicsObj = new GraphicsObject_TextureFlat(
		ModelManager::Get("LEMON_DEFAULT_CUBE"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE"),
		TextureManager::Get("LEMON_DEFAULT_TILE")
	);

	// submit registration for draw calls
	Drawable::SubmitRegistration();

	// submit registration for update calls
	Updatable::SubmitRegistration();

	// set up our collision, starting with setting our group (type)
	SetCollidableGroup<ExampleCube>();
	// next, we set our collision model
	SetCollisionModel(myGraphicsObj->getModel(), AABB);
	// finally, we submit registration for collision
	Collidable::SubmitRegistration();
}

ExampleCube::~ExampleCube()
{
	// clean up our graphics object
	delete myGraphicsObj;
}

void ExampleCube::Update()
{
	// translate our cube on the x axis by our move speed
	myWorldMat = Matrix(TRANS, Vect(myMoveSpeed, 0.0f, 0.0f)) * myWorldMat;

	// update our graphic object's world matrix
	myGraphicsObj->SetWorld(myWorldMat);

	// update our collision data
	UpdateCollisionData(myWorldMat);
}

void ExampleCube::Draw3D()
{
	// render our graphics object to the currently active camera
	myGraphicsObj->Render(SceneManager::GetActiveCamera());
}

void ExampleCube::Alarm0()
{
	// swap direction
	myMoveSpeed = -myMoveSpeed;
}

void ExampleCube::Collision(ExampleCube* otherCube)
{
	otherCube;  // need to reference the paramter to avoid c++ compile warnings
				// in this context the parameter doesn't matter

	// collided with other cube, change direction
	myMoveSpeed = -myMoveSpeed;
	// set an alarm to automatically change direction again in 3 seconds
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 3.0f);
}
