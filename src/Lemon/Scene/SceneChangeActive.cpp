#include "SceneChangeActive.h"
#include "SceneManagerAttorney.h"

SceneChangeActive::SceneChangeActive()
	: m_pScene(nullptr) {}

void SceneChangeActive::Process()
{
	SceneManagerAttorney::ChangeScene(m_pScene);
}

void SceneChangeActive::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}
