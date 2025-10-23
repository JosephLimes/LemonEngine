#ifndef _DrawableManager
#define _DrawableManager

#include <list>

class Drawable;

class DrawableManager
{
public:
	// Type for updatables to store a reference in our list
	using ListRef = std::list<Drawable*>::iterator;

	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator = (const DrawableManager&) = delete;
	~DrawableManager() = default;

protected:
	std::list<Drawable*>				m_registeredObjs;

public:
	void								Register(Drawable* pDrawable, ListRef& ref);
	void								Deregister(const ListRef& ref);
	virtual void						ProcessElements();

};

#endif _DrawableManager