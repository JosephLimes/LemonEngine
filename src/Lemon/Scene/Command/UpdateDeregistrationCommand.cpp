#include "UpdateDeregistrationCommand.h"
#include "GameObject/UpdatableAttorney.h"

UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updatable* pUpdatable)
	: m_pUpdatable(pUpdatable) {}

void UpdateDeregistrationCommand::Execute()
{
	UpdatableAttorney::Registration::Deregister(m_pUpdatable);
}
