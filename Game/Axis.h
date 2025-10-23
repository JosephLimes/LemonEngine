#ifndef _Axis
#define _Axis

#include "GameObject\GameObject.h"

class Frigate;

class Axis : public GameObject
{
public:
	Axis();
	Axis(const Axis&) = delete;
	Axis& operator = (const Axis&) = delete;
	~Axis();

	void									Draw3D() override;
	void									Collision(Frigate* pFrigate);
	void									SetWorld(Matrix& world);
private:
	bool									m_colliding;
	GraphicsObject_TextureFlat*				m_pBase;
	GraphicsObject_TextureFlat*				m_pArrows;
};

#endif _Axis