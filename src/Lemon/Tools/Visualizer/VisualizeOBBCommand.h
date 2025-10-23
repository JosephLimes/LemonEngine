#ifndef _VisualizeOBBCommand
#define _VisualizeOBBCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"

class Visualizer;

class VisualizeOBBCommand : public Command
{
public:
	VisualizeOBBCommand() = delete;
	VisualizeOBBCommand(const VisualizeOBBCommand&) = delete;
	VisualizeOBBCommand& operator = (const VisualizeOBBCommand&) = delete;
	~VisualizeOBBCommand() = default;

	VisualizeOBBCommand(Matrix& worldOBB, const Vect& color);

private:
	Matrix			m_worldOBB;
	Vect			m_color;

public:
	void			Initialize(Matrix& worldOBB, const Vect& color);
	void			Execute() override;
};

#endif _VisualizeOBBCommand