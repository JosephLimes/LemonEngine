#ifndef _ManipTrans
#define _ManipTrans

#include "AzulCore.h"

#include "EditorInputStrategy.h"

class ManipTrans : public EditorInputStrategy
{
public:
	ManipTrans(EditorAdmin* pAdmin);
	ManipTrans() = delete;
	ManipTrans(const ManipTrans&) = delete;
	ManipTrans& operator = (const ManipTrans&) = delete;
	virtual ~ManipTrans();

	virtual void	ProcessInputs() override;
	virtual void	Draw() override;

private:
	GraphicsObject_TextureFlat* m_pArrows;
};

#endif _ManipTrans;