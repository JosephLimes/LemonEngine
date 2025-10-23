#include "FontManager.h"
#include "Sprite/SpriteFont.h"

FontManager* FontManager::m_pInstance;

FontManager::FontManager()
{
	// Load defaults
	privLoad("LEMON_DEFAULT_ARIAL", "arial_bold_12");
}

FontManager::~FontManager()
{
	for (std::pair<std::string, SpriteFont*> item : m_loadedFonts)
	{
		delete item.second;
	}
	m_loadedFonts.clear();
}

FontManager& FontManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new FontManager;
	}
	return *m_pInstance;
}

void FontManager::privLoad(std::string id, std::string path)
{
	if (m_loadedFonts.find(id) != m_loadedFonts.end()) // id isn't unique
	{
		Trace::out("LOAD ERROR: Font ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	SpriteFont* pFont = new SpriteFont(path);
	m_loadedFonts.insert(std::pair<std::string, SpriteFont*>(id, pFont));
}

SpriteFont* FontManager::privGet(std::string id)
{
	if (m_loadedFonts.find(id) == m_loadedFonts.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Font ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedFonts.find(id)->second;
}

void FontManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}