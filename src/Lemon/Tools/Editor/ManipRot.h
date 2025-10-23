#ifndef _ManipRot
#define _ManipRot

#include "AzulCore.h"

#include "EditorInputStrategy.h"

class ManipRot : public EditorInputStrategy
{
public:
	ManipRot(EditorAdmin* pAdmin);
	ManipRot() = delete;
	ManipRot(const ManipRot&) = delete;
	ManipRot& operator = (const ManipRot&) = delete;
	virtual ~ManipRot();

	virtual void	ProcessInputs() override;
	virtual void	Draw() override;

private:
	GraphicsObject_TextureFlat* m_pGO;
};

#endif _ManipRot;