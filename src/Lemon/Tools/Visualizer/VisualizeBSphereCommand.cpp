#include "VisualizeBSphereCommand.h"
#include "VisualizerAttorney.h"

VisualizeBSphereCommand::VisualizeBSphereCommand(Matrix & worldBS, const Vect & color)
	: m_worldBS(worldBS), m_color(color)
{}

void VisualizeBSphereCommand::Initialize(Matrix& worldBS, const Vect& color)
{
	m_worldBS = worldBS;
	m_color = color;
}

void VisualizeBSphereCommand::Execute()
{
	VisualizerAttorney::RenderBSphere(m_worldBS, m_color);
	VisualizerAttorney::RecycleCmd(this);
}
