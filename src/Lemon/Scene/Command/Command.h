#ifndef _Command
#define _Command

class Command
{
public:
	Command() = default;
	Command(const Command&) = delete;
	Command& operator = (const Command&) = delete;
	virtual ~Command() = default;

	virtual void			Execute() = 0;
};

#endif _Command