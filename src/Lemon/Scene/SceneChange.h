#ifndef _SceneChange
#define _SceneChange

class SceneChange
{
public:
	SceneChange() = default;
	SceneChange(const SceneChange&) = default;
	SceneChange& operator = (const SceneChange&) = delete;
	virtual ~SceneChange() = default;

	virtual void		Process() = 0;
};

#endif _SceneChange