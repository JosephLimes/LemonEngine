#ifndef _VisualizeBSphereCommand
#define _VisualizeBSphereCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"

class Visualizer;

class VisualizeBSphereCommand : public Command
{
public:
	VisualizeBSphereCommand() = delete;
	VisualizeBSphereCommand(const VisualizeBSphereCommand&) = delete;
	VisualizeBSphereCommand& operator = (const VisualizeBSphereCommand&) = delete;
	~VisualizeBSphereCommand() = default;

	VisualizeBSphereCommand(Matrix& worldBS, const Vect& color);

private:
	Matrix			m_worldBS;
	Vect			m_color;

public:
	void			Initialize(Matrix& worldBS, const Vect& color);
	void			Execute() override;
};

#endif _VisualizeBSphereCommand