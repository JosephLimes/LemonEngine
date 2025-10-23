#ifndef _SpriteString
#define _SpriteString

#include <vector>
#include "SpriteFont.h"

class SpriteString
{
public:
	SpriteString(SpriteFont* pFont, std::string string, float x, float y);
	SpriteString() = default;
	SpriteString(const SpriteString&) = default;
	SpriteString& operator = (const SpriteString&) = default;
	~SpriteString() = default;

private:
	SpriteFont*						m_pFont;
	std::vector<SpriteFont::Glyph*>	m_glyphs;

	float							m_height;
	float							m_width;
	float							m_x;
	float							m_y;

public:
	void							Render();

	float							GetHeight();
	float							GetWidth();

	float							GetX();
	float							GetY();

	void							SetPos(float x, float y);
	void							Set(SpriteFont* pFont, std::string string, float x, float y);

};

#endif _SpriteString