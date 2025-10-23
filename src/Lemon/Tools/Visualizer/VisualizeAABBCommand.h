#ifndef _VisualizeAABBCommand
#define _VisualizeAABBCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"

class Visualizer;

class VisualizeAABBCommand : public Command
{
public:
	VisualizeAABBCommand() = delete;
	VisualizeAABBCommand(const VisualizeAABBCommand&) = delete;
	VisualizeAABBCommand& operator = (const VisualizeAABBCommand&) = delete;
	~VisualizeAABBCommand() = default;

	VisualizeAABBCommand(Matrix& worldAABB, const Vect& color);

private:
	Matrix			m_worldAABB;
	Vect			m_color;

public:
	void			Initialize(Matrix& worldAABB, const Vect& color);
	void			Execute() override;
};

#endif _VisualizeAABBCommand