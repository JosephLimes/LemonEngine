#include "ImageManager.h"

ImageManager* ImageManager::m_pInstance;

ImageManager::~ImageManager()
{
	for (std::pair<std::string, Image*> item : m_loadedImages)
	{
		delete item.second;
	}
	m_loadedImages.clear();
}

ImageManager& ImageManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new ImageManager;
	}
	return *m_pInstance;
}

void ImageManager::privLoad(std::string id, Texture* pTex)
{
	if (m_loadedImages.find(id) != m_loadedImages.end()) // id isn't unique
	{
		Trace::out("LOAD ERROR: Image ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	Image* pImage = new Image(pTex, new Rect(0.0f, 0.0f, (float)pTex->getWidth(), (float)pTex->getHeight()));
	m_loadedImages.insert(std::pair<std::string, Image*>(id, pImage));
}

void ImageManager::privLoad(std::string id, Texture* pTex, Rect* pRect)
{
	if (m_loadedImages.find(id) != m_loadedImages.end()) // id isn't unique
	{
		Trace::out("LOAD ERROR: Image ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}
	Image* pImage = new Image(pTex, pRect);
	m_loadedImages.insert(std::pair<std::string, Image*>(id, pImage));
}

Image* ImageManager::privGet(std::string id)
{
	if (m_loadedImages.find(id) == m_loadedImages.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Image ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedImages.find(id)->second;
}

void ImageManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}