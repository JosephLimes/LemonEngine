#ifndef _SpriteFont
#define _SpriteFont

#include <map>
#include <string>
#include <xmllite.h>

class Sprite;
class Texture;

class SpriteFont
{
public:
	using Key = int;
	using Glyph = Sprite;

private:
	using FontMap = std::map< Key, Glyph* >;

	std::string			m_name;
	Texture*			m_pTexture;
	FontMap				m_fontmap;

	// Parse the XML file
	void XMLtoCollection(std::string filename);

	// Tool: Reads & converts an XML attribute into an int
	void ElementTextToInt(IXmlReader* pReader, int& out);

	// Add the character to the font map
	void AddCharToMap(int key, float x, float y, float w, float h);

public:
	SpriteFont() = delete;
	SpriteFont(std::string path);
	~SpriteFont();
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;

	Glyph*	GetGlyph(char c);
	float	GetHeight();
};

#endif _SpriteFont