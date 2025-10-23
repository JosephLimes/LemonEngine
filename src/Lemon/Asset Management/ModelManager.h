#ifndef _ModelManager
#define _ModelManager

#include <map>

#include "AzulCore.h"



class ModelManager
{
	friend class ModelManagerAttorney;

private: 
	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator = (const ModelManager&) = delete;
	~ModelManager();

	static ModelManager*			m_pInstance;
	std::map<std::string, Model*>	m_loadedModels;

	static ModelManager&			Instance();

public:
	static void						Load(std::string id, std::string path) { Instance().privLoad(id, path); };
	static void						Load(std::string id, int sizeXZ, int repeatU, int repeatV) { Instance().privLoad(id, sizeXZ, repeatU, repeatV); };
	static void						Load(std::string id, const Model::PreMadeModels& model) { Instance().privLoad(id, model); };
	static Model*					Get(std::string id) { return Instance().privGet(id); };

private:
	static void						Terminate();
	void							privLoad(std::string id, std::string path);
	void							privLoad(std::string id, int sizeXZ, int repeatU, int repeatV);
	void							privLoad(std::string id, const Model::PreMadeModels& model);
	Model*							privGet(std::string id);
};

#endif _ModelManager