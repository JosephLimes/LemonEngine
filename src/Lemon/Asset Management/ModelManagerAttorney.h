#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
public:
	friend class Lemon;

	ModelManagerAttorney() = delete;
	ModelManagerAttorney(const ModelManagerAttorney&) = delete;
	ModelManagerAttorney& operator = (const ModelManagerAttorney&) = delete;
	~ModelManagerAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { ModelManager::Terminate(); };
};

#endif _ModelManagerAttorney