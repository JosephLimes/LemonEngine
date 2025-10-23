#include "UpdateRegistrationCommand.h"
#include "GameObject/UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* pUpdatable)
	: m_pUpdatable(pUpdatable) {}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::Register(m_pUpdatable);
}
