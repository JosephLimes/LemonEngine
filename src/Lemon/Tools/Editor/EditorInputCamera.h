#ifndef _EditorInputCamera
#define _EditorInputCamera

#include "EditorInputStrategy.h"

class EditorInputCamera : public EditorInputStrategy
{
public:
	EditorInputCamera(EditorAdmin* pAdmin);
	EditorInputCamera(const EditorInputCamera&) = delete;
	EditorInputCamera& operator = (const EditorInputCamera&) = delete;
	virtual ~EditorInputCamera() = default;

	virtual void	ProcessInputs() override;
};

#endif _EditorInputCamera