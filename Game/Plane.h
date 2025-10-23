#ifndef _Plane
#define _Plane

#include "GameObject\GameObject.h"

class Plane : public GameObject
{
public:
	Plane();
	Plane(const Plane&) = delete;
	Plane& operator = (const Plane&) = delete;
	~Plane();

	void									Draw3D() override;
private:
	GraphicsObject_TextureFlat*				m_pGraphicsObj;
};

#endif _Plane