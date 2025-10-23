#ifndef _ShaderManager
#define _ShaderManager

#include <map>

#include "AzulCore.h"

class ShaderManager
{
	friend class ShaderManagerAttorney;

private: 
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator = (const ShaderManager&) = delete;
	~ShaderManager();

	static ShaderManager*					m_pInstance;
	std::map<std::string, ShaderObject*>	m_loadedShaders;

	static ShaderManager&					Instance();

public:
	static void								Load(std::string id, std::string path) { Instance().privLoad(id, path); };
	static ShaderObject*					Get(std::string id) { return Instance().privGet(id); };

private:
	static void								Terminate();
	void									privLoad(std::string id, std::string path);
	ShaderObject*							privGet(std::string id);
};

#endif _ShaderManager