#include "Frigate.h"
#include "Asset Management/ShaderManager.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/TextureManager.h"
#include "Camera Management/CameraManager.h"
#include "Scene/SceneManager.h"
#include "TestScene.h"
#include "Scene/Scene.h"

#include "Tools/Visualizer/Visualizer.h"
#include "Tools/LemonMath.h"

#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Terrain/Terrain.h"
#include "Time Management/TimeManager.h"

Frigate::Frigate()
	: m_active(false), m_colliding(false), m_pGraphicsObjLight(nullptr), m_pGOeditor(nullptr)
{
	//SubmitEntry();
}

void Frigate::Update()
{
	float frameShipSpeed = m_shipTransSpeed * TimeManager::GetFrameTime();

	if (m_active)
	{
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
		{
			m_world = Matrix(ROT_Y, m_shipRotAng) * m_world;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
		{
			m_world = Matrix(ROT_Y, -m_shipRotAng) * m_world;
		}

		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
		{
			m_world = Matrix(TRANS, Vect(0, 0, frameShipSpeed)) * m_world;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
		{
			m_world = Matrix(TRANS, Vect(0, 0, -frameShipSpeed)) * m_world;
		}
	}
	// Spaceship adjust matrix
	m_pGraphicsObjLight->SetWorld(m_world);
	m_pGOeditor->SetWorld(m_world);

	UpdateCollisionData(m_world);

	if (m_active)
	{
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
		{
			m_shipRotTrans = Matrix(ROT_Y, m_shipRotAng) * m_shipRotTrans;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
		{
			m_shipRotTrans = Matrix(ROT_Y, -m_shipRotAng) * m_shipRotTrans;
		}

		// Ship translation movement (not using time-based values for simplicity)
		if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
		{
			m_shipRotTrans = Matrix(TRANS, Vect(0, 0, frameShipSpeed)) * m_shipRotTrans;
		}
		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
		{
			m_shipRotTrans = Matrix(TRANS, Vect(0, 0, -frameShipSpeed)) * m_shipRotTrans;
		}
	}


	Vect pos = m_world.get(ROW_3);
	Vect n = SceneManager::GetActiveScene().TerrainNormAt(pos);
	float h = SceneManager::GetActiveScene().TerrainHeightAt(pos);
	Vect r = n.cross(m_shipRotTrans.get(ROW_2));
	Vect up = r.cross(n);

	pos[y] = h;
	m_world = Matrix(ROT_ORIENT, up, n) * Matrix(TRANS, pos) * Matrix(TRANS, Vect(0,15,0));

	// Spaceship adjust matrix

	//m_world = m_shipScale * m_shipRotTrans;
	m_pGraphicsObjLight->SetWorld(m_world);
	m_pGOeditor->SetWorld(m_world);

	UpdateCollisionData(m_world);
}

void Frigate::Collision(Axis*)
{
	m_colliding = true;
}

void Frigate::Collision(Frigate*)
{
	m_colliding = true;
}

void Frigate::Collision()
{
	m_colliding = true;
}

void Frigate::CollisionTerrain()
{
	m_colliding = true;
}

void Frigate::SetWorld(Matrix& world)
{
	m_shipRotTrans = world;
}

void Frigate::SetActive(bool state)
{
	m_active = state;
}

void Frigate::LevelInitialize()
{
	m_shipRotTrans = m_world;

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	m_pGraphicsObjLight = new GraphicsObject_TextureLight(ModelManager::Get("SpaceFrigate"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("SpaceFrigate"),
		LightColor,
		LightPos);
	m_shipScale.set(SCALE, 1, 1, 1);
	Matrix world = m_shipScale * Matrix(ROT_Y, 0) * m_shipRotTrans;
	m_pGraphicsObjLight->SetWorld(world);

	m_pGOeditor = new GraphicsObject_TextureLight(ModelManager::Get("LEMON_DEFAULT_CUBE"),
		ShaderManager::Get("LEMON_DEFAULT_TEXTURE_LIGHT"),
		TextureManager::Get("FrigateCube"),
		LightColor,
		LightPos);
	m_pGOeditor->SetWorld(world);

	SetCollidableGroup<Frigate>();
	SetCollisionModel(m_pGraphicsObjLight->getModel(), BSPHERE);

	SubmitEntry();
}

void Frigate::LevelTerminate()
{
	Drawable::SubmitDeregistration();
	Updatable::SubmitDeregistration();
	Collidable::SubmitDeregistration();

	SubmitExit();
}

void Frigate::SceneEntry()
{
	Drawable::SubmitRegistration();
	Updatable::SubmitRegistration();
	Collidable::SubmitRegistration();
}

void Frigate::SceneExit()
{
	delete this;
}

void Frigate::Draw3D()
{
	m_pGraphicsObjLight->Render(SceneManager::GetActiveCamera());

	if (m_colliding)
	{
		//Visualizer::ShowCollisionVolume(GetCollisionVolume(), Colors::Red);
	}
	else
	{
		//Visualizer::ShowCollisionVolume(GetCollisionVolume());
	}
	m_colliding = false;
}

//void Frigate::DrawEditor3D()
//{
//	m_pGOeditor->Render(SceneManager::GetActiveCamera());
//}

Frigate::~Frigate()
{
	if (m_pGraphicsObjLight) delete m_pGraphicsObjLight;
	if (m_pGOeditor) delete m_pGOeditor;
}