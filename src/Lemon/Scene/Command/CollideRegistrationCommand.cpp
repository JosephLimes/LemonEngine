#include "CollideRegistrationCommand.h"
#include "GameObject/CollidableAttorney.h"

CollideRegistrationCommand::CollideRegistrationCommand(Collidable* pCollidable)
	: m_pCollidable(pCollidable) {}

void CollideRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::Register(m_pCollidable);
}
