#include "TextureManager.h"

TextureManager* TextureManager::m_pInstance;

TextureManager::TextureManager()
{
	// load default assets
	privLoad("LEMON_DEFAULT_TILE", "LEMON_DEFAULT_TILE.tga");
}

TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> item : m_loadedTextures)
	{
		delete item.second;
	}
	m_loadedTextures.clear();
}

TextureManager& TextureManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new TextureManager;
	}
	return *m_pInstance;
}

void TextureManager::privLoad(std::string id, std::string path)
{
	if (m_loadedTextures.find(id) != m_loadedTextures.end()) // id isn't unique
	{
		Trace::out("LOAD ERROR: Texture ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	path = "Textures/" + path;
	Texture* pTexture = new Texture(path.c_str());
	m_loadedTextures.insert(std::pair<std::string, Texture*>(id, pTexture));
}

Texture* TextureManager::privGet(std::string id)
{
	if (m_loadedTextures.find(id) == m_loadedTextures.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Texture ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedTextures.find(id)->second;
}

void TextureManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}