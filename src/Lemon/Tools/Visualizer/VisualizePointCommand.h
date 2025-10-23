#ifndef _VisualizePointCommand
#define _VisualizePointCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"

class Visualizer;

class VisualizePointCommand : public Command
{
public:
	VisualizePointCommand() = delete;
	VisualizePointCommand(const VisualizePointCommand&) = delete;
	VisualizePointCommand& operator = (const VisualizePointCommand&) = delete;
	~VisualizePointCommand() = default;

	VisualizePointCommand(const Vect& pos, const Vect& color);

private:
	Vect			m_pos;
	Vect			m_color;

public:
	void			Initialize(const Vect& pos, const Vect& color);
	void			Execute() override;
};

#endif _VisualizePointCommand