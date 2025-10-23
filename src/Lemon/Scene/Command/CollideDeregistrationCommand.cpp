#include "CollideDeregistrationCommand.h"
#include "GameObject/CollidableAttorney.h"

CollideDeregistrationCommand::CollideDeregistrationCommand(Collidable* pCollidable)
	: m_pCollidable(pCollidable) {}

void CollideDeregistrationCommand::Execute()
{
	CollidableAttorney::Registration::Deregister(m_pCollidable);
}
