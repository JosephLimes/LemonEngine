#ifndef _LevelObject
#define _LevelObject

#include "AzulCore.h"
#include "MapFile.h"
#include "GameObject/GameObject.h"

#define DEF_FUNC_LVL_ID													\
	LevelTypeID GetTypeID() override									\
	{																	\
		std::string typeStr(__FUNCSIG__);								\
		unsigned int typeStartIndex = 24;								\
		unsigned int typeEndIndex = typeStr.find(':', typeStartIndex);	\
		unsigned int typeLen = typeEndIndex - typeStartIndex;			\
		typeStr = typeStr.substr(typeStartIndex, typeLen);				\
		std::hash<std::string> strHash;									\
		unsigned int hash = strHash(typeStr);							\
		return hash;													\
	};																	\

class LevelObject : public GameObject
{
	friend class LevelObjectAttorney;

public:
	LevelObject() = default;
	LevelObject(const LevelObject&) = delete;
	LevelObject& operator = (const LevelObject&) = delete;
	virtual ~LevelObject() = default;

	virtual void			Serialize(char* const buffer, LevelObjectFlags flags);

	virtual LevelTypeID		GetTypeID() = 0;
	virtual void			LevelInitialize() = 0;
	virtual void			LevelTerminate() = 0;

protected:
	Matrix					m_world;

private:
	void					SetLevelWorldMat(Matrix& world);
	Matrix&					GetLevelWorldMat();
};

#endif _LevelObject