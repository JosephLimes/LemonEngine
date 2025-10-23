#ifndef _LevelObjectBaseFactory
#define _LevelObjectBaseFactory

class LevelObject;

class LevelObjectBaseFactory
{
public:
	LevelObjectBaseFactory(std::string typeName)
		: m_type(typeName) {}
	LevelObjectBaseFactory() = delete;
	LevelObjectBaseFactory(const LevelObjectBaseFactory&) = delete;
	LevelObjectBaseFactory& operator = (const LevelObjectBaseFactory&) = delete;
	virtual ~LevelObjectBaseFactory() = default;

	virtual LevelObject*	Create() = 0;

	std::string	GetTypeName()
	{
		return m_type;
	}

protected:
	std::string m_type;
};

#endif _LevelObjectBaseFactory