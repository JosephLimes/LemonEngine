#include "DrawDeregistrationCommand.h"
#include "GameObject/DrawableAttorney.h"

DrawDeregistrationCommand::DrawDeregistrationCommand(Drawable* pDrawable)
	: m_pDrawable(pDrawable) {}

void DrawDeregistrationCommand::Execute()
{
	DrawableAttorney::Registration::Deregister(m_pDrawable);
}
