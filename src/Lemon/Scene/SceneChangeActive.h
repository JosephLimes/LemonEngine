#ifndef _SceneChangeActive
#define _SceneChangeActive

#include "SceneChange.h"

class Scene;

class SceneChangeActive : public SceneChange
{
public:
	SceneChangeActive();
	SceneChangeActive(const SceneChangeActive&) = default;
	SceneChangeActive& operator = (const SceneChangeActive&) = delete;
	~SceneChangeActive() = default;

	virtual void		Process() override;

	void				SetScene(Scene* pScene);

private:
	Scene*				m_pScene;
};

#endif _SceneChangeActive