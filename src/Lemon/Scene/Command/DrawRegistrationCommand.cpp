#include "DrawRegistrationCommand.h"
#include "GameObject/DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* pDrawable)
	: m_pDrawable(pDrawable) {}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::Register(m_pDrawable);
}
