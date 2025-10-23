#include "ModelManager.h"

ModelManager* ModelManager::m_pInstance;

ModelManager::ModelManager()
{
	// load default assets
	privLoad("LEMON_DEFAULT_SPRITE", Model::PreMadeModels::UnitSquareXY);
	privLoad("LEMON_DEFAULT_SPHERE", Model::PreMadeModels::UnitSphere);
	privLoad("LEMON_DEFAULT_CUBE", Model::PreMadeModels::UnitBox_WF);
}

ModelManager::~ModelManager()
{
	for (std::pair<std::string, Model*> item : m_loadedModels)
	{
		delete item.second;
	}
	m_loadedModels.clear();
}

ModelManager& ModelManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new ModelManager;
	}
	return *m_pInstance;
}

void ModelManager::privLoad(std::string id, std::string path)
{
	if (m_loadedModels.find(id) != m_loadedModels.end()) // id is not unique
	{
		Trace::out("LOAD ERROR: Model ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	path = "Models/" + path;
	Model* pModel = new Model(path.c_str());
	m_loadedModels.insert(std::pair<std::string, Model*>(id, pModel));
}

void ModelManager::privLoad(std::string id, int sizeXZ, int repeatU, int repeatV)
{
	if (m_loadedModels.find(id) != m_loadedModels.end()) // id is not unique
	{
		Trace::out("LOAD ERROR: Model ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	Model* pModel = new Model(sizeXZ, repeatU, repeatV);
	m_loadedModels.insert(std::pair<std::string, Model*>(id, pModel));
}

void ModelManager::privLoad(std::string id, const Model::PreMadeModels& model)
{
	if (m_loadedModels.find(id) != m_loadedModels.end()) // id is not unique
	{
		Trace::out("LOAD ERROR: Model ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	Model* pModel = new Model(model);
	m_loadedModels.insert(std::pair<std::string, Model*>(id, pModel));
}

Model* ModelManager::privGet(std::string id)
{
	if (m_loadedModels.find(id) == m_loadedModels.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Model ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedModels.find(id)->second;
}

void ModelManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}