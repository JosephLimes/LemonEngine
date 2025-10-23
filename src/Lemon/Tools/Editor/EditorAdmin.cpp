#include "EditorAdmin.h"

#include <fstream>

#include "Time Management/TimeManager.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Asset Management/TerrainManagerAttorney.h"
#include "Scene/SceneManager.h"
#include "Tools/Colors.h"
#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"
#include "../Lemon.h"
#include "Collision/Volumes/CollisionVolumeBSphere.h"
#include "Scene/Scene.h"

#include "LevelObjectManager.h"
#include "../ScreenLog/ScreenLog.h"
#include "MapFileParser.h"
#include "LevelObjectAttorney.h"
#include "LevelObjectNull.h"
#include "LevelObject.h"
#include "ManipTrans.h"
#include "ManipRot.h"
#include "ManipScale.h"
#include "EditorUI.h"
#include "EditorCam.h"
#include "EditorInputCamera.h"
#include "EditorInputMarker.h"

#include "../Game/Frigate.h"

EditorAdmin::EditorAdmin(EditorUI* pUI)
	:	m_pUI(pUI),
		m_fileName("../Maps/default.lmf"),
		m_pCam(new EditorCam(this)),
		m_pNullLvlObj(new LevelObjectNull()),
		m_pSelected(m_pNullLvlObj),
		m_terrainIt(TerrainManagerAttorney::GetIt("LEMON_EDITOR_GRID")),
		m_pManipTrans(new ManipTrans(this)),
		m_pManipRot(new ManipRot(this)),
		m_pManipScale(new ManipScale(this)),
		m_pManipActive(m_pManipTrans),
		m_pAxis(new GraphicsObject_TextureFlat(ModelManager::Get("widget"), ShaderManager::Get("LEMON_DEFAULT_TEXTURE"), TextureManager::Get("widget"))),
		m_widgetScaleFactor(1.0f),
		m_speed(1.0f),
		m_pInputCam(new EditorInputCamera(this)),
		m_pInputMarker(new EditorInputMarker(this)),
		m_pInputActive(m_pInputMarker),
		m_pInputPrev(m_pInputMarker)
{
	m_pUI->SetAdmin(this);

	Updatable::SubmitRegistration();
	Drawable::SubmitRegistration();

	Vect color = Colors::GreenYellow;
	m_pGOMarker = new GraphicsObject_WireframeConstantColor
	(
		ModelManager::Get("LEMON_DEFAULT_CUBE"),
		ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"),
		color
	);

	m_world = Matrix(IDENTITY);
	Matrix world = Matrix(SCALE, 10, 10, 10) * m_world;
	m_pGOMarker->SetWorld(world);


	// editor controls registration

	Inputable::SubmitRegistration(AZUL_MOUSE::BUTTON_LEFT, ButtonEvent::BUTTON_PRESS);		// select obj
	Inputable::SubmitRegistration(AZUL_MOUSE::BUTTON_RIGHT, ButtonEvent::BUTTON_PRESS);		// switch to camera control
	Inputable::SubmitRegistration(AZUL_MOUSE::BUTTON_RIGHT, ButtonEvent::BUTTON_RELEASE);	// switch from camera control
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F1, KeyEvent::KEY_PRESS);					// write objects to file
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F2, KeyEvent::KEY_PRESS);					// read objects from file
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F3, KeyEvent::KEY_PRESS);					// clear level
	Inputable::SubmitRegistration(AZUL_KEY::KEY_SPACE, KeyEvent::KEY_PRESS);				// place obj of selected type
	Inputable::SubmitRegistration(AZUL_KEY::KEY_ARROW_LEFT, KeyEvent::KEY_PRESS);			// cycle type selection prev
	Inputable::SubmitRegistration(AZUL_KEY::KEY_ARROW_RIGHT, KeyEvent::KEY_PRESS);			// cycle type selection next
	Inputable::SubmitRegistration(AZUL_KEY::KEY_Z, KeyEvent::KEY_PRESS);					// toggle updatable property
	Inputable::SubmitRegistration(AZUL_KEY::KEY_X, KeyEvent::KEY_PRESS);					// toggle drawable property
	Inputable::SubmitRegistration(AZUL_KEY::KEY_C, KeyEvent::KEY_PRESS);					// toggle collidable property
	Inputable::SubmitRegistration(AZUL_KEY::KEY_E, KeyEvent::KEY_PRESS);					// scale selected obj
	Inputable::SubmitRegistration(AZUL_KEY::KEY_R, KeyEvent::KEY_PRESS);					// rotate selected obj
	Inputable::SubmitRegistration(AZUL_KEY::KEY_T, KeyEvent::KEY_PRESS);					// translate selected obj
	Inputable::SubmitRegistration(AZUL_KEY::KEY_DELETE, KeyEvent::KEY_PRESS);				// delete selected obj
	Inputable::SubmitRegistration(AZUL_KEY::KEY_ARROW_UP, KeyEvent::KEY_PRESS);				// speed up
	Inputable::SubmitRegistration(AZUL_KEY::KEY_ARROW_DOWN, KeyEvent::KEY_PRESS);			// speed down
	Inputable::SubmitRegistration(AZUL_KEY::KEY_LEFT_BRACKET, KeyEvent::KEY_PRESS);			// cycle terrain prev
	Inputable::SubmitRegistration(AZUL_KEY::KEY_RIGHT_BRACKET, KeyEvent::KEY_PRESS);		// cycle terrain next
}

EditorAdmin::~EditorAdmin()
{
	delete m_pGOMarker;
	delete m_pCam;
	delete m_pNullLvlObj;
	delete m_pManipTrans;
	delete m_pManipRot;
	delete m_pManipScale;
	delete m_pAxis;
	delete m_pInputCam;
	delete m_pInputMarker;

	for (LevelObject* pObj : m_levelObjs)
	{
		delete pObj;
	}

	LevelObjectManager::Terminate();
}

void EditorAdmin::Update()
{
	m_pInputActive->ProcessInputs();
	Matrix widgetWorld = Matrix(SCALE, Vect(m_widgetScaleFactor, m_widgetScaleFactor, m_widgetScaleFactor)) * LevelObjectAttorney::GetLevelWorld(m_pSelected);
	m_pAxis->SetWorld(widgetWorld);
}

void EditorAdmin::Draw2D()
{
	Visualizer::ShowCollisionVolume(m_pSelected->GetCollisionVolume());

	glClear(GL_DEPTH_BUFFER_BIT);
	m_pGOMarker->Render(SceneManager::GetActiveCamera());
	if (m_pManipActive != m_pManipRot) // kind of a band-aid
	{
		m_pAxis->Render(SceneManager::GetActiveCamera());
	}
	m_pInputActive->Draw();
}

void EditorAdmin::KeyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_F1:
		DebugMsg::out("Writing level data to file.\n");
		WriteToFile();
		break;
	case AZUL_KEY::KEY_F2:
		DebugMsg::out("Constructing level from file.\n");
		ReadFromFile();
		break;
	case AZUL_KEY::KEY_F3:
		DebugMsg::out("Clearing current level.\n");
		ClearLevel();
		break;
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("Placing object.\n");
		PlaceSelectedType();
		break;
	case AZUL_KEY::KEY_ARROW_LEFT:
		DebugMsg::out("Selecting prev type.\n");
		LevelObjectManager::DecrementSelected();
		break;
	case AZUL_KEY::KEY_ARROW_RIGHT:
		DebugMsg::out("Selecting next type.\n");
		LevelObjectManager::IncrementSelected();
		break;
	case AZUL_KEY::KEY_Z:
		DebugMsg::out("Toggling updatable property.\n");
		m_selectedFlags.Flip(LevelObjectFlagValue::UPDATABLE);
		if (m_pSelected != m_pNullLvlObj) // editing an existing obj
		{
			auto flagit = m_flagsList.begin() + m_flagInd;
			(*flagit).Flip(LevelObjectFlagValue::UPDATABLE);
		}
		break;
	case AZUL_KEY::KEY_X:
		DebugMsg::out("Toggling drawable property.\n");
		m_selectedFlags.Flip(LevelObjectFlagValue::DRAWABLE);
		if (m_pSelected != m_pNullLvlObj) // editing an existing obj
		{
			auto flagit = m_flagsList.begin() + m_flagInd;
			(*flagit).Flip(LevelObjectFlagValue::DRAWABLE);
		}
		break;
	case AZUL_KEY::KEY_C:
		DebugMsg::out("Toggling collidable property.\n");
		m_selectedFlags.Flip(LevelObjectFlagValue::COLLIDABLE);
		if (m_pSelected != m_pNullLvlObj) // editing an existing obj
		{
			auto flagit = m_flagsList.begin() + m_flagInd;
			(*flagit).Flip(LevelObjectFlagValue::COLLIDABLE);
		}
		break;
	case AZUL_KEY::KEY_E:
		if (m_pInputActive == m_pManipScale)
		{
			DebugMsg::out("Toggling scale mode off.\n");
			m_pInputActive = m_pInputMarker;
			m_pInputPrev = m_pInputMarker;
		}
		else
		{
			DebugMsg::out("Toggling scale mode on.\n");
			m_pManipActive = m_pManipScale;
			m_pInputActive = m_pManipActive;
			m_pInputPrev = m_pManipActive;
		}
		break;
	case AZUL_KEY::KEY_R:
		if (m_pInputActive == m_pManipRot)
		{
			DebugMsg::out("Toggling rotate mode off.\n");
			m_pInputActive = m_pInputMarker;
			m_pInputPrev = m_pInputMarker;
		}
		else
		{
			DebugMsg::out("Toggling rotate mode on.\n");
			m_pManipActive = m_pManipRot;
			m_pInputActive = m_pManipActive;
			m_pInputPrev = m_pManipActive;
		}
		break;
	case AZUL_KEY::KEY_T:
		if (m_pInputActive == m_pManipTrans)
		{
			DebugMsg::out("Toggling translate mode off.\n");
			m_pInputActive = m_pInputMarker;
			m_pInputPrev = m_pInputMarker;
		}
		else
		{
			DebugMsg::out("Toggling translate mode on.\n");
			m_pManipActive = m_pManipTrans;
			m_pInputActive = m_pManipActive;
			m_pInputPrev = m_pManipActive;
		}
		break;
	case AZUL_KEY::KEY_DELETE:
		DebugMsg::out("Deleting selected object.\n");
		DeleteSelected();
		break;
	case AZUL_KEY::KEY_ARROW_UP:
		DebugMsg::out("Raising marker speed.\n");
		RaiseSpeed();
		break;
	case AZUL_KEY::KEY_ARROW_DOWN:
		DebugMsg::out("Lowering marker speed.\n");
		LowerSpeed();
		break;
	case AZUL_KEY::KEY_LEFT_BRACKET:
		DebugMsg::out("Selecting prev terrain.\n");
		SelectPrevTerrain();
		break;
	case AZUL_KEY::KEY_RIGHT_BRACKET:
		DebugMsg::out("Selecting next terrain.\n");
		SelectNextTerrain();
		break;
	}
}

void EditorAdmin::MousePressed(AZUL_MOUSE button)
{
	if (button == AZUL_MOUSE::BUTTON_LEFT)
	{
		SelectObject();
	}
	else if (button == AZUL_MOUSE::BUTTON_RIGHT)
	{
		Trace::out("Camera control\n");
		glfwDisable(GLFW_MOUSE_CURSOR);
		m_pInputActive = m_pInputCam;
	}
}

void EditorAdmin::MouseReleased(AZUL_MOUSE button)
{
	button;
	Trace::out("Normal control\n");
	glfwEnable(GLFW_MOUSE_CURSOR);
	m_pInputActive = m_pInputPrev;
}

void EditorAdmin::PlaceSelectedType()
{
	LevelObject* pNew = LevelObjectManager::GetSelectedFactory()->Create();
	LevelObjectAttorney::SetLevelWorld(pNew, m_world);
	pNew->LevelInitialize();
	MapFileParser::ParseFlags(pNew, m_selectedFlags);

	m_levelObjs.insert(m_levelObjs.end(), pNew);
	m_flagsList.insert(m_flagsList.end(), m_selectedFlags);
}

void EditorAdmin::ReadFromFile()
{
	MapFileParser::ReadMapFile(m_fileName, m_levelObjs, m_flagsList, this);
}

void EditorAdmin::WriteToFile()
{
	MapFileParser::WriteMapFile(m_fileName, m_levelObjs, m_flagsList, (*m_terrainIt).first);
}

void EditorAdmin::ClearLevel()
{
	for (LevelObject* lvlObj : m_levelObjs)
	{
		lvlObj->LevelTerminate();
	}

	m_levelObjs.clear();
	m_flagsList.clear();
	m_pSelected = m_pNullLvlObj;
}

void EditorAdmin::SelectObject()
{
	if (!m_levelObjs.empty()) // we cant select objects that dont exist...
	{
		int ix, iy;
		Lemon::getMousePosition(ix, iy);
		float x = float(ix);
		float y = float(iy);

		// manually create screen to NDC
		Vect v0 = Vect(2.0f / float(Lemon::GetWidth()), 0.0f, 0.0f, 0.0f);
		Vect v1 = Vect(0.0f, -2.0f / float(Lemon::GetHeight()), 0.0f, 0.0f);
		Vect v2 = Vect(0.0f, 0.0f, 2.0f, 0.0f);
		Vect v3 = Vect(-1.0f, 1.0f, -1.0f, 1.0f);
		Matrix scr2ndc(v0, v1, v2, v3);

		Matrix perspInv = m_pCam->GetProjMatrix().getInv();

		Matrix v2w = m_pCam->GetViewMatrix().getInv();

		Vect p0(x, y, 0.0f, 1.0f); // near point
		Vect p1(x, y, 1.0f, 1.0f); // far point

		// apply inverse matricies
		p0 *= scr2ndc;
		p0 *= perspInv;
		p0 *= v2w;
		p1 *= scr2ndc;
		p1 *= perspInv;
		// homogenous coord. division, only matters for far point here
		p1[X] = p1[X] / p1[W];
		p1[Y] = p1[Y] / p1[W];
		p1[Z] = p1[Z] / p1[W];
		p1[W] = 1.0f;
		p1 *= v2w;

		//Visualizer::ShowSegment(p0, p1);

		std::vector<LevelObject*> colliding; // store every object that collides with ray to determine which is closest later

		// test ray collision
		auto it = m_levelObjs.begin();
		while (it != m_levelObjs.end())
		{
			// test against BSpheres first
			if (LemonMath::Intersect((*it)->GetBSphere(), p0, p1 - p0))
			{
				// test against proper collision volume
				if ((*it)->GetCollisionVolume().IntersectAccept(p0, p1 - p0))
				{
					colliding.push_back((*it));
				}
			}
			it++;
		}

		// test all objects that passed to assess distance
		if (!colliding.empty())
		{
			auto closestIt = colliding.begin();
			it = colliding.begin();
			float closestDistance = ((*it++)->GetBSphere().GetCenter() - p0).magSqr(); // initialize with first value, then iterate to prepare for loop
			while (it != colliding.end())
			{
				float distance = ((*it)->GetBSphere().GetCenter() - p0).magSqr();
				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestIt = it;
				}
				it++;
			}

			m_pSelected = (*closestIt);
			auto loIt = find(m_levelObjs.begin(), m_levelObjs.end(), m_pSelected);
			m_flagInd = loIt - m_levelObjs.begin();
			auto flagIt = m_flagsList.begin() + m_flagInd;
			m_selectedFlags = (*flagIt);
			UpdateWidgetScale();
		}

		else
		{
			m_pSelected = m_pNullLvlObj;
			m_pInputPrev = m_pInputMarker;
			m_pInputActive = m_pInputMarker;
		}
	}
}

void EditorAdmin::DeleteSelected()
{
	if (m_pSelected != m_pNullLvlObj) // dont delete the null obj!
	{
		// find item to delete
		auto it = std::find(m_levelObjs.begin(), m_levelObjs.end(), m_pSelected);
		// index will be the same for flags
		int ind = it - m_levelObjs.begin();

		// delete
		(*it)->LevelTerminate();
		m_levelObjs.erase(it);
		auto it2 = m_flagsList.begin() + ind;
		m_flagsList.erase(it2);

		m_pSelected = m_pNullLvlObj;
	}
}

void EditorAdmin::UpdateWidgetScale()
{
	// widget length is 10u, set length to max of 10u or half of BSphere radius
	m_widgetScaleFactor = std::max(1.0f, 0.1f * m_pSelected->GetBSphere().GetRadius() / 2);
}

void EditorAdmin::RaiseSpeed()
{
	m_speed *= 2.0f;
}

void EditorAdmin::LowerSpeed()
{
	m_speed *= 0.5f;
}

void EditorAdmin::SelectPrevTerrain()
{
	m_terrainIt = TerrainManagerAttorney::GetPrev(m_terrainIt);
	SceneManager::SetActiveTerrain((*m_terrainIt).first);

	m_pUI->SetTerrain((*m_terrainIt).first);
}

void EditorAdmin::SelectNextTerrain()
{
	m_terrainIt = TerrainManagerAttorney::GetNext(m_terrainIt);
	SceneManager::SetActiveTerrain((*m_terrainIt).first);

	m_pUI->SetTerrain((*m_terrainIt).first);
}

void EditorAdmin::UpdateTerrain(std::string id)
{
	m_terrainIt = TerrainManagerAttorney::GetIt(id);
	SceneManager::SetActiveTerrain((*m_terrainIt).first);

	m_pUI->SetTerrain((*m_terrainIt).first);
}

void EditorAdmin::SetFileName(std::string name)
{
	m_fileName = "../Maps/" + name + ".lmf";
}

void EditorAdmin::ManipulateSelected(Matrix& in)
{
	Matrix world = in * LevelObjectAttorney::GetLevelWorld(m_pSelected);
	LevelObjectAttorney::SetLevelWorld(m_pSelected, world);
}

void EditorAdmin::ProcessCameraInput()
{
	m_pCam->ProcessInputs();
}

void EditorAdmin::SetMarkerWorld(Matrix& world)
{
	m_world = world;

	// Update marker position
	Matrix markerworld = Matrix(SCALE, 10, 10, 10) * m_world;
	m_pGOMarker->SetWorld(markerworld);
}

Matrix EditorAdmin::GetMarkerWorld() const
{
	return m_world;
}

Matrix EditorAdmin::GetSelectedWorld() const
{
	return LevelObjectAttorney::GetLevelWorld(m_pSelected);
}

float EditorAdmin::GetWidgetScaleFactor() const
{
	return m_widgetScaleFactor;
}

float EditorAdmin::GetSpeed() const
{
	return m_speed;
}

LevelObjectFlags EditorAdmin::GetFlags() const
{
	return m_selectedFlags;
}
