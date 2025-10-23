#include "EditorDrawableManager.h"
#include "Tools/Editor/LevelObjectAttorney.h"
#include "GameObject/DrawableAttorney.h"

void EditorDrawableManager::ProcessElements()
{
	// Draw 3D objects
	for (Drawable* pObj : m_registeredObjs)
	{
		DrawableAttorney::GameLoop::DrawEditor3D(pObj);
	}

	// Draw sprites
	for (Drawable* pObj : m_registeredObjs)
	{
		DrawableAttorney::GameLoop::DrawEditor2D(pObj);
	}
}
