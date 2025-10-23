#include "VisualizeAABBCommand.h"
#include "VisualizerAttorney.h"

VisualizeAABBCommand::VisualizeAABBCommand(Matrix & worldAABB, const Vect & color)
	: m_worldAABB(worldAABB), m_color(color)
{}

void VisualizeAABBCommand::Initialize(Matrix& worldAABB, const Vect& color)
{
	m_worldAABB = worldAABB;
	m_color = color;
}

void VisualizeAABBCommand::Execute()
{
	VisualizerAttorney::RenderAABB(m_worldAABB, m_color);
	VisualizerAttorney::RecycleCmd(this);
}
