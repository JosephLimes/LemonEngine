#include "VisualizePointCommand.h"
#include "VisualizerAttorney.h"

VisualizePointCommand::VisualizePointCommand(const Vect& pos, const Vect & color)
	: m_pos(pos), m_color(color)
{}

void VisualizePointCommand::Initialize(const Vect& pos, const Vect& color)
{
	m_pos = pos;
	m_color = color;
}

void VisualizePointCommand::Execute()
{
	VisualizerAttorney::RenderPoint(m_pos, m_color);
	VisualizerAttorney::RecycleCmd(this);
}
