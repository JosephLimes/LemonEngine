#ifndef _Sprite
#define _Sprite

#include "AzulCore.h"

class Sprite
{
public:
	Sprite(std::string imageID);
	Sprite() = delete;
	Sprite(const Sprite&) = delete;
	Sprite& operator = (const Sprite&) = delete;
	~Sprite();

private:
	GraphicsObject_Sprite*	m_pGOS;

	Matrix					m_offset;
	Matrix					m_trans;
	Matrix					m_rot;
	Matrix					m_scale;
	Matrix					m_world;

	float					m_angle;
	float					m_centerX;
	float					m_centerY;
	float					m_scaleX;
	float					m_scaleY;

public:
	void					Render();

	float					GetHeight();
	float					GetWidth();
	float					GetAngle();
	void					SetAngle(float angle);
	void					SetPos(float x, float y);
	void					SetScaleFactor(float scaleX, float scaleY);
	void					SetScalePixel(float width, float height);
	void					SetCenter(float x, float y);
	
};

#endif _Sprite