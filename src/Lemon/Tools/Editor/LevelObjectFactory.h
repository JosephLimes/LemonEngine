#ifndef _LevelObjectFactory
#define _LevelObjectFactory

#include "LevelObjectBaseFactory.h"

template<class T>
class LevelObjectFactory : public LevelObjectBaseFactory
{
public:
	LevelObjectFactory(std::string typeName)
		: LevelObjectBaseFactory(typeName)	{}

	LevelObjectFactory() = delete;
	LevelObjectFactory(const LevelObjectFactory&) = delete;
	LevelObjectFactory& operator = (const LevelObjectFactory&) = delete;
	~LevelObjectFactory() = default;

	virtual LevelObject* Create() override
	{
		return new T();
	}
};

#endif _LevelObjectFactory
