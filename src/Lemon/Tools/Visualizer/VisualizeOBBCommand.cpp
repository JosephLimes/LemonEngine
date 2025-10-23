#include "VisualizeOBBCommand.h"
#include "VisualizerAttorney.h"

VisualizeOBBCommand::VisualizeOBBCommand(Matrix & worldOBB, const Vect & color)
	: m_worldOBB(worldOBB), m_color(color)
{}

void VisualizeOBBCommand::Initialize(Matrix& worldOBB, const Vect& color)
{
	m_worldOBB = worldOBB;
	m_color = color;
}

void VisualizeOBBCommand::Execute()
{
	VisualizerAttorney::RenderOBB(m_worldOBB, m_color);
	VisualizerAttorney::RecycleCmd(this);
}
