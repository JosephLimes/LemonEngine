#ifndef _LevelObjectManager
#define _LevelObjectManager

#include <map>
#include "LevelObject.h"
#include "LevelObjectFactory.h"

class LevelObjectManager
{
private:
	LevelObjectManager();
	LevelObjectManager(const LevelObjectManager&) = delete;
	LevelObjectManager& operator = (const LevelObjectManager&) = delete;
	~LevelObjectManager();

	static LevelObjectManager*		m_pInstance;

	std::map<LevelTypeID, LevelObjectBaseFactory*> m_typeMap;
	std::map<LevelTypeID, LevelObjectBaseFactory*>::iterator m_selectedIt;
	LevelObjectBaseFactory*			m_selected;

	static LevelObjectManager&		Instance();


public:
	static void						Terminate(); // public for testing

	template <typename T>
	static void RegisterType()
	{
		LevelObjectManager& instance = Instance();

		// grab function signature as string and calculate the subsection that contains the type
		std::string typeStr(__FUNCSIG__);
		size_t typeStartIndex = 52; // this will probably stay hardcoded, I always know the format of __FUNCSIG__ for this particular function
		size_t typeEndIndex = typeStr.find('>', typeStartIndex);
		size_t typeLen = typeEndIndex - typeStartIndex;

		// get substring of only type name
		typeStr = typeStr.substr(typeStartIndex, typeLen);

		// create a hash of type name
		std::hash<std::string> strHash;
		LevelTypeID hash = strHash(typeStr);
		DebugMsg::out("Registering type ");
		Trace::out(typeStr.c_str());
		DebugMsg::out(" with TypeID %zu\n", hash);

		// create our T factory, insert into hashmap with typename hash as key
		LevelObjectBaseFactory* pBaseFac = new LevelObjectFactory<T>(typeStr);
		instance.m_selectedIt = instance.m_typeMap.insert({ hash, pBaseFac }).first;

		// set most recently added as our current selected type
		instance.m_selected = pBaseFac;
	}

	static LevelObject*				Get(LevelTypeID ID) { return Instance().privGet(ID); }
	static LevelObjectBaseFactory*	GetSelectedFactory() { return Instance().privGetSelectedFactory(); }
	static void						DecrementSelected() { Instance().privDecrementSelected(); }
	static void						IncrementSelected() { Instance().privIncrementSelected(); }

private:
	LevelObject*					privGet(LevelTypeID ID);
	LevelObjectBaseFactory*			privGetSelectedFactory();
	void							privDecrementSelected();
	void							privIncrementSelected();
};

#endif _LevelObjectManager