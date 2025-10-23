#ifndef _EditorInputMarker
#define _EditorInputMarker

#include "EditorInputStrategy.h"

class EditorInputMarker : public EditorInputStrategy
{
public:
	EditorInputMarker(EditorAdmin* pAdmin);
	EditorInputMarker(const EditorInputMarker&) = delete;
	EditorInputMarker& operator = (const EditorInputMarker&) = delete;
	virtual ~EditorInputMarker() = default;

	virtual void	ProcessInputs() override;
};

#endif _EditorInputMarker