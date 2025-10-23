#ifndef _ImageManager
#define _ImageManager

#include <map>

#include "AzulCore.h"

class Texture;



class ImageManager
{
	friend class ImageManagerAttorney;

private:
	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator = (const ImageManager&) = delete;
	~ImageManager();

	static ImageManager*				m_pInstance;
	std::map<std::string, Image*>		m_loadedImages;

	static ImageManager& Instance();

public:
	static void							Load(std::string id, Texture* pTex) { Instance().privLoad(id, pTex); };
	static void							Load(std::string id, Texture* pTex, Rect* pRect) { Instance().privLoad(id, pTex, pRect); };
	static Image*						Get(std::string id) { return Instance().privGet(id); };

private:
	static void							Terminate();
	void								privLoad(std::string id, Texture* pTex);
	void								privLoad(std::string id, Texture* pTex, Rect* pRect);
	Image*								privGet(std::string id);
};

#endif _ImageManager