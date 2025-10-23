#ifndef _TextureManager
#define _TextureManager

#include <map>

#include "AzulCore.h"

class TextureManager
{
	friend class TextureManagerAttorney;

private: 
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator = (const TextureManager&) = delete;
	~TextureManager();

	static TextureManager*				m_pInstance;
	std::map<std::string, Texture*>		m_loadedTextures;

	static TextureManager&				Instance();

public:
	static void							Load(std::string id, std::string path) { Instance().privLoad(id, path); };
	static Texture*						Get(std::string id) { return Instance().privGet(id); };

private:
	static void							Terminate();
	void								privLoad(std::string id, std::string path);
	Texture*							privGet(std::string id);
};

#endif _TextureManager