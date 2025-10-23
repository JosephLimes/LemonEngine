#include "VisualizeSegmentCommand.h"
#include "VisualizerAttorney.h"

VisualizeSegmentCommand::VisualizeSegmentCommand(const Vect& pos1, const Vect& pos2, const Vect & color)
	: m_pos1(pos1), m_pos2(pos2), m_color(color)
{}

void VisualizeSegmentCommand::Initialize(const Vect& pos1, const Vect& pos2, const Vect& color)
{
	m_pos1 = pos1;
	m_pos2 = pos2;
	m_color = color;
}

void VisualizeSegmentCommand::Execute()
{
	VisualizerAttorney::RenderSegment(m_pos1, m_pos2, m_color);
	VisualizerAttorney::RecycleCmd(this);
}
