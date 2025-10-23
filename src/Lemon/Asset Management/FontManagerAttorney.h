#ifndef _FontManagerAttorney
#define _FontManagerAttorney

#include "FontManager.h"

class FontManagerAttorney
{
public:
	friend class Lemon;

	FontManagerAttorney() = delete;
	FontManagerAttorney(const FontManagerAttorney&) = delete;
	FontManagerAttorney& operator = (const FontManagerAttorney&) = delete;
	~FontManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { FontManager::Terminate(); };
};

#endif _FontManagerAttorney