#ifndef _ExampleCube
#define _ExampleCube

#include "GameObject/GameObject.h"

class ExampleCube : public GameObject
{
public:
	ExampleCube();
	~ExampleCube();
	void Update() override;
	void Draw3D() override;
	void Alarm0() override;
	void Collision(ExampleCube* otherCube);

	GraphicsObject_TextureFlat* myGraphicsObj;
	Matrix myWorldMat;
	float myMoveSpeed;
};

#endif _ExampleCube