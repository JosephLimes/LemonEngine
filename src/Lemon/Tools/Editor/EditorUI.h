#ifndef _EditorUI
#define _EditorUI

#include "GameObject/GameObject.h"
#include "MapFile.h"

class EditorAdmin;
class SpriteFont;
class SpriteString;

class EditorUI : public GameObject
{
public:
	EditorUI();
	EditorUI(const EditorUI&) = delete;
	EditorUI& operator = (const EditorUI&) = delete;
	~EditorUI();

	void				Update() override;
	void				Draw2D() override;

	void				KeyPressed(AZUL_KEY key) override;
	void				KeyTyped(char c) override;

	void				SetAdmin(EditorAdmin* pAdmin);

	void				SetTerrain(std::string id);

private:
	EditorAdmin*		m_pAdmin;
	SpriteFont*			m_pFont;
	SpriteString*		m_pVersionStr;
	LevelObjectFlags	m_selectedFlags;

	std::string			m_filename;
	std::string			m_terrainID;
};

#endif _EditorUI