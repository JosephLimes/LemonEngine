#include "EditorUI.h"
#include "../ScreenLog/ScreenLog.h"
#include "LevelObjectManager.h"
#include "EditorAdmin.h"
#include "Asset Management/FontManager.h"
#include "Sprite/SpriteString.h"

EditorUI::EditorUI()
	:	m_pFont(FontManager::Get("LEMON_DEFAULT_ARIAL")),
		m_pVersionStr(new SpriteString(m_pFont, " File Format Version: " + std::to_string(LEMON_MAP_FILE_VERSION), 0.0f, m_pFont->GetHeight())),
		m_filename("\tdefault.lmf"),
		m_terrainID("\t<none selected>")
{
	Updatable::SubmitRegistration();
	Drawable::SubmitRegistration();
	Inputable::SubmitRegistration(AZUL_KEY::KEY_ENTER, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistrationTyped();

	// Set up basic UI using mostly screenlog

	// Top row displays file controls
	ScreenLog::Add(
		" F1 - Save to file     F2 - Load from file     F3 - Clear level"
	);
	ScreenLog::Add(" Current File:");
	ScreenLog::Add(&m_filename[0]);
	ScreenLog::Add("");

	ScreenLog::Add(" WASD - Move directionally");
	ScreenLog::Add(" Shift - Move up");
	ScreenLog::Add(" Ctrl - Move down");
	ScreenLog::Add(" Space - Place selected type");
	ScreenLog::Add(" [ and ] - Cycle selected terrain");
	ScreenLog::Add(" L and R arrow - Cycle selected type");
	ScreenLog::Add(" U and D arrow - Change speed");
	ScreenLog::Add("");

	ScreenLog::Add(" Currently selected type:");

	if (LevelObjectManager::GetSelectedFactory())
	{
		std::string str = LevelObjectManager::GetSelectedFactory()->GetTypeName();
		str = "\t<" + str + ">";

		// stupid workaround to cast std::string to char* instead of const char*
		char* selected = new char[str.size() + 1];
		strcpy_s(selected, str.size() + 1, str.c_str());

		ScreenLog::Add(selected);
		delete[] selected;
	}
	else
	{
		ScreenLog::Add("\tNo level objects are currently registered.");
	}

	ScreenLog::Add("");
	ScreenLog::Add("\t Set on level initialize:");
	ScreenLog::Add("\t Z - [ ] Updatable");
	ScreenLog::Add("\t X - [ ] Drawable");
	ScreenLog::Add("\t C - [ ] Collidable");

	ScreenLog::Add("");
	ScreenLog::Add(" Selected Object Manipulation");
	ScreenLog::Add(" \tdel - Delete");
	ScreenLog::Add(" \tE - Scale");
	ScreenLog::Add(" \tR - Rotate");
	ScreenLog::Add(" \tT - Translate");

	ScreenLog::Add("");
	ScreenLog::Add(" Selected Terrain:");
	char* terr = new char[m_terrainID.size() + 1];
	strcpy_s(terr, m_terrainID.size() + 1, m_terrainID.c_str());
	ScreenLog::Add(terr);
	delete[] terr;
}

EditorUI::~EditorUI()
{
	delete m_pVersionStr;
}

void EditorUI::Update()
{
	// does NOT need to be queried every frame, just here as scaffolding.
	// when UI gets proper overhaul, admin will call updates as necessary

	if (LevelObjectManager::GetSelectedFactory())
	{
		std::string str = LevelObjectManager::GetSelectedFactory()->GetTypeName();
		str = "\t<" + str + ">";

		// stupid workaround to cast std::string to char* instead of const char*
		char* selected = new char[str.size() + 1];
		strcpy_s(selected, str.size() + 1, str.c_str());

		ScreenLog::Edit(13, selected);
		delete[] selected;
	}

	if (m_selectedFlags != m_pAdmin->GetFlags())
	{
		m_selectedFlags = m_pAdmin->GetFlags();

		if (m_selectedFlags.Check(LevelObjectFlagValue::UPDATABLE))
		{
			ScreenLog::Edit(16, "\t Z - [*] Updatable");
		}
		else
		{
			ScreenLog::Edit(16, "\t Z - [ ] Updatable");
		}

		if (m_selectedFlags.Check(LevelObjectFlagValue::DRAWABLE))
		{
			ScreenLog::Edit(17, "\t X - [*] Drawable");
		}
		else
		{
			ScreenLog::Edit(17, "\t X - [ ] Drawable");
		}

		if (m_selectedFlags.Check(LevelObjectFlagValue::COLLIDABLE))
		{
			ScreenLog::Edit(18, "\t C - [*] Collidable");
		}
		else
		{
			ScreenLog::Edit(18, "\t C - [ ] Collidable");
		}
	}
}

void EditorUI::Draw2D()
{
	m_pVersionStr->Render();
}

void EditorUI::KeyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_ENTER) // toggle file name entry
	{
		SceneManager::GetActiveScene().SetInputMode(InputMode::TYPED);
		m_filename.clear();
		std::string fileDisplay = "\t" + m_filename + ".lmf";
		ScreenLog::Edit(2, &fileDisplay[0]);
	}
}

void EditorUI::KeyTyped(char c)
{
	if (c == 38) // ENTER - finished entering filename
	{
		SceneManager::GetActiveScene().SetInputMode(InputMode::STANDARD);
		m_pAdmin->SetFileName(m_filename);
		return;
	}
	if (c == 32) // SPACE - change to underscore for now until I figure out shift as a modifier
	{
		c = 95;
		m_filename += c;
	}
	if (c == 39) // BACKSPACE - remove a character instead of adding
	{
		if (!m_filename.empty()) m_filename.pop_back();
	}
	// else, just add the character to the string as long as its alphanumeric
	else if ((c >= 65 && c <= 90) || (c >= 48 && c <= 57))
	{
		m_filename += c;
	}

	std::string fileDisplay = "\t" + m_filename + ".lmf";
	ScreenLog::Edit(2, &fileDisplay[0]);
}

void EditorUI::SetAdmin(EditorAdmin* pAdmin)
{
	m_pAdmin = pAdmin;
}

void EditorUI::SetTerrain(std::string id)
{
	if (id == "LEMON_EDITOR_GRID")
	{
		m_terrainID = "\t<none selected>"; // default editor grid is not 'selectable'
	}
	else
	{
		m_terrainID = "\t<" + id + ">";
	}

	// stupid workaround to cast std::string to char* instead of const char*
	char* terr = new char[m_terrainID.size() + 1];
	strcpy_s(terr, m_terrainID.size() + 1, m_terrainID.c_str());

	ScreenLog::Edit(27, terr);

	delete[] terr;
}
