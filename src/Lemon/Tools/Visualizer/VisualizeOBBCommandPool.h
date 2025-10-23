#ifndef _VisualizeOBBCommandPool
#define _VisualizeOBBCommandPool

#include <stack>

class Matrix;
class Vect;
class VisualizeOBBCommand;

class VisualizeOBBCommandPool
{
public:
	VisualizeOBBCommandPool() = default;
	VisualizeOBBCommandPool(const VisualizeOBBCommandPool&) = default;
	VisualizeOBBCommandPool operator = (const VisualizeOBBCommandPool&) = delete;
	~VisualizeOBBCommandPool();

private:
	std::stack<VisualizeOBBCommand*>	m_commands;

public:
	VisualizeOBBCommand*				GetCommand(Matrix& world, const Vect& color);
	void								RecycleCommand(VisualizeOBBCommand* pCmd);
};

#endif _VisualizeOBBCommandPool