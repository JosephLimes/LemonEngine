#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
public:
	friend class Lemon;

	ShaderManagerAttorney() = delete;
	ShaderManagerAttorney(const ShaderManagerAttorney&) = delete;
	ShaderManagerAttorney& operator = (const ShaderManagerAttorney&) = delete;
	~ShaderManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { ShaderManager::Terminate(); };
};

#endif _ShaderManagerAttorney