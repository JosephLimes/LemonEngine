#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
public:
	friend class Lemon;

	TextureManagerAttorney() = delete;
	TextureManagerAttorney(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney& operator = (const TextureManagerAttorney&) = delete;
	~TextureManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { TextureManager::Terminate(); };
};

#endif _TextureManagerAttorney