#ifndef _VisualizeSegmentCommand
#define _VisualizeSegmentCommand

#include "AzulCore.h"

#include "Scene/Command/Command.h"

class Visualizer;

class VisualizeSegmentCommand : public Command
{
public:
	VisualizeSegmentCommand() = delete;
	VisualizeSegmentCommand(const VisualizeSegmentCommand&) = delete;
	VisualizeSegmentCommand& operator = (const VisualizeSegmentCommand&) = delete;
	~VisualizeSegmentCommand() = default;

	VisualizeSegmentCommand(const Vect& pos1, const Vect& pos2, const Vect& color);

private:
	Vect			m_pos1;
	Vect			m_pos2;
	Vect			m_color;

public:
	void			Initialize(const Vect& pos1, const Vect& pos2, const Vect& color);
	void			Execute() override;
};

#endif _VisualizeSegmentCommand