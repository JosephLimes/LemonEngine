#ifndef _SceneChangeNull
#define _SceneChangeNull

#include "SceneChange.h"

class SceneChangeNull : public SceneChange
{
public:
	SceneChangeNull() = default;
	SceneChangeNull(const SceneChangeNull&) = default;
	SceneChangeNull& operator = (const SceneChangeNull&) = delete;
	~SceneChangeNull() = default;

	virtual void		Process() override;
};

#endif _SceneChangeNull