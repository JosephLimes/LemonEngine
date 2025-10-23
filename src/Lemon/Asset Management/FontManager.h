#ifndef _FontManager
#define _FontManager

#include <map>

#include "AzulCore.h"

class SpriteFont;

class FontManager
{
	friend class FontManagerAttorney;

private: 
	FontManager();
	FontManager(const FontManager&) = delete;
	FontManager& operator = (const FontManager&) = delete;
	~FontManager();

	static FontManager*					m_pInstance;
	std::map<std::string, SpriteFont*>	m_loadedFonts;

	static FontManager&					Instance();

public:
	static void							Load(std::string id, std::string path) { Instance().privLoad(id, path); };
	static SpriteFont*					Get(std::string id) { return Instance().privGet(id); };

private:
	static void							Terminate();
	void								privLoad(std::string id, std::string path);
	SpriteFont*							privGet(std::string id);
};

#endif _FontManager