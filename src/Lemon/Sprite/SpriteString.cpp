#include "SpriteString.h"
#include "Sprite.h"
#include "Scene/SceneManager.h"

SpriteString::SpriteString(SpriteFont* pFont, std::string string, float x, float y)
	: m_pFont(pFont), m_height(0.0f), m_width(0.0f), m_x(x), m_y(y)
{
	// get glyph pointers for each character and add to string
	for (char c : string)
	{
		SpriteFont::Glyph* glyph = m_pFont->GetGlyph(c);
		m_glyphs.push_back(glyph);
		m_width += glyph->GetWidth();
	}

	m_height = m_pFont->GetHeight();
}

void SpriteString::Render()
{
	float x = m_x;
	float y = m_y;
	for (SpriteFont::Glyph* glyph : m_glyphs)
	{
		glyph->SetPos(x, y);
		glyph->Render();
		x += glyph->GetWidth();
	}
}

float SpriteString::GetHeight()
{
	return m_height;
}

float SpriteString::GetWidth()
{
	return m_width;
}

float SpriteString::GetX()
{
	return m_x;
}

float SpriteString::GetY()
{
	return m_y;
}

void SpriteString::SetPos(float x, float y)
{
	m_x = x;
	m_y = y;
}

void SpriteString::Set(SpriteFont* pFont, std::string string, float x, float y)
{
	m_width = 0.0f;
	m_pFont = pFont;
	m_glyphs.clear();
	m_x = x;
	m_y = y;
	for (char c : string)
	{
		SpriteFont::Glyph* glyph = m_pFont->GetGlyph(c);
		m_glyphs.push_back(glyph);
		m_width += glyph->GetWidth();
	}
	m_height = m_glyphs[0]->GetHeight();
}
