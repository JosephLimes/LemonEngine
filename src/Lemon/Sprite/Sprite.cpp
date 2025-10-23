#include "Sprite.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ImageManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"

Sprite::Sprite(std::string imageID)
	:	m_pGOS(new GraphicsObject_Sprite(ModelManager::Get("LEMON_DEFAULT_SPRITE"), ShaderManager::Get("LEMON_DEFAULT_SPRITE"), ImageManager::Get(imageID), ImageManager::Get(imageID)->pImageRect)),
		m_angle(0.0f),
		m_centerX(0.0f),
		m_centerY(0.0f),
		m_scaleX(1.0f),
		m_scaleY(1.0f),
		m_offset(Matrix(IDENTITY)),
		m_scale(Matrix(IDENTITY)),
		m_rot(Matrix(IDENTITY)),
		m_trans(Matrix(IDENTITY)),
		m_world(Matrix(IDENTITY))
{}

Sprite::~Sprite()
{
	delete m_pGOS;
}

void Sprite::Render()
{
	m_world = m_offset * m_scale * m_rot * m_trans;
	m_pGOS->SetWorld(m_world);
	m_pGOS->Render(SceneManager::GetSpriteCamera());
}

float Sprite::GetHeight()
{
	return m_pGOS->origHeight;
}

float Sprite::GetWidth()
{
	return m_pGOS->origWidth;
}

float Sprite::GetAngle()
{
	return m_angle;
}

void Sprite::SetAngle(float angle)
{
	m_angle = angle;
	m_rot.set(ROT_Z, angle);

}

void Sprite::SetPos(float x, float y)
{
	m_trans.set(TRANS, x, y, 0);
}

void Sprite::SetScaleFactor(float scaleX, float scaleY)
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;

	m_scale.set(SCALE, m_scaleX, m_scaleY, 1);
}

void Sprite::SetScalePixel(float width, float height)
{
	m_scaleX = width / m_pGOS->origWidth / 2;
	m_scaleY = height / m_pGOS->origHeight / 2;

	m_scale.set(SCALE, m_scaleX, m_scaleY, 1);
}

void Sprite::SetCenter(float x, float y)
{
	// convert from model coordinate (0,0 is center of sprite) to sprite coordinate (0,0 is top left of sprite)
	m_centerX = x + m_pGOS->origWidth / 2;
	m_centerY = y - m_pGOS->origHeight / 2;

	m_offset.set(TRANS, m_centerX, m_centerY, 0);
}
