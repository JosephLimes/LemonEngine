#include "DrawableManager.h"
#include "GameObject/DrawableAttorney.h"

void DrawableManager::Register(Drawable* pDrawable, ListRef& ref)
{
	ref = m_registeredObjs.insert(m_registeredObjs.end(), pDrawable);
}

void DrawableManager::Deregister(const ListRef& ref)
{
	m_registeredObjs.erase(ref);
}

void DrawableManager::ProcessElements()
{
	// Draw 3D objects
	for (Drawable* pObj : m_registeredObjs)
	{
		DrawableAttorney::GameLoop::Draw3D(pObj);
	}

	// Draw sprites
	for (Drawable* pObj : m_registeredObjs)
	{
		DrawableAttorney::GameLoop::Draw2D(pObj);
	}
}
