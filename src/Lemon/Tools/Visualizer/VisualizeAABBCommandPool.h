#ifndef _VisualizeAABBCommandPool
#define _VisualizeAABBCommandPool

#include <stack>

class Matrix;
class Vect;
class VisualizeAABBCommand;

class VisualizeAABBCommandPool
{
public:
	VisualizeAABBCommandPool() = default;
	VisualizeAABBCommandPool(const VisualizeAABBCommandPool&) = default;
	VisualizeAABBCommandPool operator = (const VisualizeAABBCommandPool&) = delete;
	~VisualizeAABBCommandPool();

private:
	std::stack<VisualizeAABBCommand*>	m_commands;

public:
	VisualizeAABBCommand*				GetCommand(Matrix& world, const Vect& color);
	void								RecycleCommand(VisualizeAABBCommand* pCmd);
};

#endif _VisualizeAABBCommandPool