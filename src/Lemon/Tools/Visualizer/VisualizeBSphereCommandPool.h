#ifndef _VisualizeBSphereCommandPool
#define _VisualizeBSphereCommandPool

#include <stack>

class Matrix;
class Vect;
class VisualizeBSphereCommand;

class VisualizeBSphereCommandPool
{
public:
	VisualizeBSphereCommandPool() = default;
	VisualizeBSphereCommandPool(const VisualizeBSphereCommandPool&) = default;
	VisualizeBSphereCommandPool operator = (const VisualizeBSphereCommandPool&) = delete;
	~VisualizeBSphereCommandPool();

private:
	std::stack<VisualizeBSphereCommand*>	m_commands;

public:
	VisualizeBSphereCommand*				GetCommand(Matrix& world, const Vect& color);
	void									RecycleCommand(VisualizeBSphereCommand* pCmd);
};

#endif _VisualizeBSphereCommandPool