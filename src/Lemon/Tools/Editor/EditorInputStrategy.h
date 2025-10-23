#ifndef _EditorInputStrategy
#define _EditorInputStrategy

class EditorAdmin;

class EditorInputStrategy
{
public:
	EditorInputStrategy() = default;
	EditorInputStrategy(const EditorInputStrategy&) = delete;
	EditorInputStrategy& operator = (const EditorInputStrategy&) = delete;
	virtual ~EditorInputStrategy() = default;

	virtual void	ProcessInputs() = 0;
	virtual void	Draw() {};

protected:
	EditorAdmin*	m_pAdmin;
};

#endif _EditorInputStrategy;