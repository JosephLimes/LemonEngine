#ifndef _EditorDrawableManager
#define _EditorDrawableManager

#include "Scene/DrawableManager.h"

class EditorDrawableManager : public DrawableManager
{
public:
	EditorDrawableManager() = default;
	EditorDrawableManager(const DrawableManager&) = delete;
	EditorDrawableManager& operator = (const EditorDrawableManager&) = delete;
	~EditorDrawableManager() = default;

	virtual void ProcessElements() override;
};

#endif _EditorDrawableManager