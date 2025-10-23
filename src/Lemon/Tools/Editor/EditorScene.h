#ifndef _EditorScene
#define _EditorScene

#include "Scene/Scene.h"

class EditorAdmin;
class EditorUI;

class EditorScene : public Scene
{
public:
	EditorScene() = default;
	EditorScene(const EditorScene&) = delete;
	EditorScene& operator = (const EditorScene&) = delete;
	~EditorScene() = default;

	virtual void Initialize();
	virtual void Terminate();

private:
	EditorAdmin*	m_pAdmin;
	EditorUI*		m_pUI;
};

#endif _EditorScene