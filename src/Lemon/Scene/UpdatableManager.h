#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>

class Updatable;

class UpdatableManager
{
public:
	// Type for updatables to store a reference in our list
	using ListRef = std::list<Updatable*>::iterator;

	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator = (const UpdatableManager&) = delete;
	~UpdatableManager() = default;

private:
	std::list<Updatable*>				m_registeredObjs;

public:
	void								Register(Updatable* pUpdatable, ListRef& ref);
	void								Deregister(const ListRef& ref);
	void								ProcessElements();

};

#endif _UpdatableManager