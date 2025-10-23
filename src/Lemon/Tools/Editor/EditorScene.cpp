#include "EditorScene.h"
#include "EditorAdmin.h"
#include "EditorUI.h"
#include "Scene/SceneAttorney.h"
#include "Asset Management/TerrainManager.h"
#include "Terrain/Terrain.h"

void EditorScene::Initialize()
{
	m_pUI = new EditorUI();
	m_pAdmin = new EditorAdmin(m_pUI);
	SetTerrain("LEMON_EDITOR_GRID");

	// switches drawable manager to use editor draw functions instead of normal draws, maybe more functionality later
	SceneAttorney::EnableEditorMode();
}

void EditorScene::Terminate()
{
	delete m_pAdmin;
	delete m_pUI;
}
