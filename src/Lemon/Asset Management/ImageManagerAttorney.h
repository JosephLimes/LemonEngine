#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
public:
	friend class Lemon;

	ImageManagerAttorney() = delete;
	ImageManagerAttorney(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney& operator = (const ImageManagerAttorney&) = delete;
	~ImageManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { ImageManager::Terminate(); };
};

#endif _ImageManagerAttorney