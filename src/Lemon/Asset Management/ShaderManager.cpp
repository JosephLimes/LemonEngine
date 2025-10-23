#include "ShaderManager.h"

ShaderManager* ShaderManager::m_pInstance;

ShaderManager::ShaderManager()
{
	// Load default assets
	privLoad("LEMON_DEFAULT_TEXTURE", "textureFlatRender");
	privLoad("LEMON_DEFAULT_TEXTURE_LIGHT", "textureLightRender");
	privLoad("LEMON_DEFAULT_SPRITE", "spriteRender");
	privLoad("LEMON_DEFAULT_COLOR_CONSTANT", "colorConstantRender");
}

ShaderManager::~ShaderManager()
{
	for (std::pair<std::string, ShaderObject*> item : m_loadedShaders)
	{
		delete item.second;
	}
	m_loadedShaders.clear();
}

ShaderManager& ShaderManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new ShaderManager;
	}
	return *m_pInstance;
}

void ShaderManager::privLoad(std::string id, std::string path)
{
	if (m_loadedShaders.find(id) != m_loadedShaders.end()) // id is not unique
	{
		Trace::out("LOAD ERROR: Shader ID '%s' is not unique!\n", id.c_str());
		assert(nullptr);
	}

	path = "Shaders/" + path;
	ShaderObject* pShader = new ShaderObject(path.c_str());
	m_loadedShaders.insert(std::pair<std::string, ShaderObject*>(id, pShader));
}

ShaderObject* ShaderManager::privGet(std::string id)
{
	if (m_loadedShaders.find(id) == m_loadedShaders.end()) // id doesn't exist
	{
		Trace::out("GET ERROR: Shader ID '%s' does not exist!\n", id.c_str());
		assert(nullptr);
	}

	return m_loadedShaders.find(id)->second;
}

void ShaderManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}