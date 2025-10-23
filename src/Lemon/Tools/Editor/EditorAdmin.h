#ifndef _EditorAdmin
#define _EditorAdmin

#include <vector>

#include "GameObject\GameObject.h"
#include "LevelObject.h"
#include "../Game/Frigate.h"

class EditorUI;
class EditorCam;
class EditorInputStrategy;
class EditorInputCamera;
class EditorInputMarker;
class ManipTrans;
class ManipRot;
class ManipScale;

class EditorAdmin : public GameObject
{
public:
	EditorAdmin(EditorUI* pUI);
	EditorAdmin() = delete;
	EditorAdmin(const EditorAdmin&) = delete;
	EditorAdmin& operator = (const EditorAdmin&) = delete;
	~EditorAdmin();

	void									Update() override;
	void									Draw2D() override;
	void									KeyPressed(AZUL_KEY key) override;
	void									MousePressed(AZUL_MOUSE button) override;
	void									MouseReleased(AZUL_MOUSE button) override;

private:
	EditorUI*								m_pUI;

	GraphicsObject_WireframeConstantColor*	m_pGOMarker;
	Matrix									m_world;
	LevelObjectFlags						m_selectedFlags;
	int										m_flagInd;

	std::vector<LevelObject*>				m_levelObjs;
	std::vector<LevelObjectFlags>			m_flagsList;

	std::string								m_fileName;

	// Currently selected object
	LevelObject*							m_pNullLvlObj;
	LevelObject*							m_pSelected;

	// Iterator to currently selected terrain
	std::map<std::string, Terrain*>::iterator m_terrainIt;

	// Editor camera fields
	EditorCam*								m_pCam;

	// object manipulation
	ManipTrans*								m_pManipTrans;
	ManipRot*								m_pManipRot;
	ManipScale*								m_pManipScale;
	EditorInputStrategy*					m_pManipActive;

	// widget base
	GraphicsObject_TextureFlat*				m_pAxis;
	float									m_widgetScaleFactor;
	float									m_speed;

	// input handling
	EditorInputCamera*						m_pInputCam;
	EditorInputMarker*						m_pInputMarker;
	EditorInputStrategy*					m_pInputActive;
	EditorInputStrategy*					m_pInputPrev;

	void									PlaceSelectedType();
	void									ReadFromFile();
	void									WriteToFile();
	void									ClearLevel();
	void									SelectObject();
	void									DeleteSelected();
	void									UpdateWidgetScale();
	void									RaiseSpeed();
	void									LowerSpeed();
	void									SelectPrevTerrain();
	void									SelectNextTerrain();

public:
	void									UpdateTerrain(std::string id);
	void									SetFileName(std::string name);
	void									ManipulateSelected(Matrix& in);
	void									ProcessCameraInput();
	void									SetMarkerWorld(Matrix& world);
	Matrix									GetMarkerWorld() const;
	Matrix									GetSelectedWorld() const;
	float									GetWidgetScaleFactor() const;
	float									GetSpeed() const;
	LevelObjectFlags						GetFlags() const;
};

#endif _EditorAdmin