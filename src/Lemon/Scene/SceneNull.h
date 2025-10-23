#ifndef _SceneNull
#define _SceneNull

#include "Scene\Scene.h"

class SceneNull : public Scene
{
public:
	SceneNull() = default;
	SceneNull(const SceneNull&) = delete;
	SceneNull& operator = (const SceneNull&) = delete;
	~SceneNull() = default;
};

#endif _SceneNull