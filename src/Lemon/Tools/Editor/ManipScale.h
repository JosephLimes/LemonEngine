#ifndef _ManipScale
#define _ManipScale

#include "AzulCore.h"

#include "EditorInputStrategy.h"

class ManipScale : public EditorInputStrategy
{
public:
	ManipScale(EditorAdmin* pAdmin);
	ManipScale() = delete;
	ManipScale(const ManipScale&) = delete;
	ManipScale& operator = (const ManipScale&) = delete;
	virtual ~ManipScale();

	virtual void	ProcessInputs() override;
	virtual void	Draw() override;

private:
	GraphicsObject_TextureFlat* m_pEnds;
};

#endif _ManipScale;