#include "Visualizer.h"
#include "Asset Management/ModelManager.h"
#include "Asset Management/ShaderManager.h"
#include "Scene/SceneManager.h"
#include "Collision/Volumes/CollisionVolumeBSphere.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Collision/Volumes/CollisionVolumeOBB.h"
#include "VisualizePointCommand.h"
#include "VisualizePointCommandPool.h"
#include "VisualizeSegmentCommand.h"
#include "VisualizeSegmentCommandPool.h"
#include "VisualizeBSphereCommand.h"
#include "VisualizeBSphereCommandPool.h"
#include "VisualizeAABBCommand.h"
#include "VisualizeAABBCommandPool.h"
#include "VisualizeOBBCommand.h"
#include "VisualizeOBBCommandPool.h"

Visualizer* Visualizer::m_pInstance;
Vect Visualizer::m_defaultColor;

Visualizer::Visualizer()
{
	m_defaultColor = Colors::LemonChiffon;
	m_pWireframeSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("LEMON_DEFAULT_SPHERE"), ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"), m_defaultColor);
	m_pWireframeBox = new GraphicsObject_WireframeConstantColor(ModelManager::Get("LEMON_DEFAULT_CUBE"), ShaderManager::Get("LEMON_DEFAULT_COLOR_CONSTANT"), m_defaultColor);
	m_pointCommandPool = new VisualizePointCommandPool();
	m_segmentCommandPool = new VisualizeSegmentCommandPool();
	m_bSphereCmdPool = new VisualizeBSphereCommandPool();
	m_AABBCmdPool = new VisualizeAABBCommandPool();
	m_OBBCmdPool = new VisualizeOBBCommandPool();
}

Visualizer::~Visualizer()
{
	delete m_pWireframeSphere;
	delete m_pWireframeBox;

	while (!m_cmdQueue.empty())
	{
		delete m_cmdQueue.front();
		m_cmdQueue.pop();
	}

	delete m_pointCommandPool;
	delete m_segmentCommandPool;
	delete m_bSphereCmdPool;
	delete m_AABBCmdPool;
	delete m_OBBCmdPool;
}

Visualizer& Visualizer::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Visualizer;
	}
	return *m_pInstance;
}

void Visualizer::ShowPoint(const Vect& pos, const Vect& color)
{
	// set up and queue command
	Visualizer& instance = Instance();
	instance.m_cmdQueue.push(instance.m_pointCommandPool->GetCommand(pos, color));
}

void Visualizer::ShowSegment(const Vect& pos1, const Vect& pos2, const Vect& color)
{
	// set up and queue command
	Visualizer& instance = Instance();
	instance.m_cmdQueue.push(instance.m_segmentCommandPool->GetCommand(pos1, pos2, color));
}

void Visualizer::ShowCollisionVolume(const CollisionVolume& colVol, const Vect& color)
{
	// pass through to the volume to callback the correct method depending on its type
	colVol.DebugView(color);
}

void Visualizer::ShowBSphere(const CollisionVolumeBSphere& bSphere, const Vect& color)
{
	// get world matrix for BSphere
	Matrix worldBS = Matrix(SCALE, bSphere.GetRadius() * Vect(1, 1, 1)) * Matrix(TRANS, bSphere.GetCenter());
	
	// set up and queue command
	Visualizer& instance = Instance();
	instance.m_cmdQueue.push(instance.m_bSphereCmdPool->GetCommand(worldBS, color));
}

void Visualizer::ShowAABB(const CollisionVolumeAABB& aabb, const Vect& color)
{
	// construct world matrix from min/max points
	Matrix worldAABB = Matrix(SCALE, aabb.GetMax() - aabb.GetMin()) * Matrix(TRANS, (aabb.GetMax() + aabb.GetMin()) * 0.5f);

	// set up and queue command
	Visualizer& instance = Instance();
	instance.m_cmdQueue.push(instance.m_AABBCmdPool->GetCommand(worldAABB, color));
}

void Visualizer::ShowOBB(const CollisionVolumeOBB& obb, const Vect& color)
{
	// construct model space matrix
	Matrix local = Matrix(SCALE, obb.GetMax() - obb.GetMin()) * Matrix(TRANS, (obb.GetMax() + obb.GetMin()) * 0.5f);

	// apply world matrix to local
	Matrix world =  local * obb.GetWorld();

	// set up and queue command
	Visualizer& instance = Instance();
	instance.m_cmdQueue.push(instance.m_OBBCmdPool->GetCommand(world, color));
}

void Visualizer::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void Visualizer::VisualizeAll()
{
	while (!m_cmdQueue.empty())
	{
		m_cmdQueue.front()->Execute();
		m_cmdQueue.pop();
	}
}

void Visualizer::privRenderPoint(const Vect& pos, const Vect& color)
{
	Matrix world = Matrix(TRANS, pos);
	m_pWireframeBox->SetWorld(world);
	m_pWireframeBox->SetColor(color);
	m_pWireframeBox->Render(SceneManager::GetActiveCamera());
}

void Visualizer::privRenderSegment(const Vect& pos1, const Vect& pos2, const Vect& color)
{
	Matrix world = Matrix(SCALE, 0.1f, 0.1f, (pos1 - pos2).mag()) * Matrix(ROT_ORIENT, (pos1 - pos2), Vect(0, 1, 0)) * Matrix(TRANS, (pos1 + pos2) * 0.5f);
	m_pWireframeBox->SetWorld(world);
	m_pWireframeBox->SetColor(color);
	m_pWireframeBox->Render(SceneManager::GetActiveCamera());
}

void Visualizer::privRenderBSphere(Matrix& worldBS, const Vect& color)
{
	m_pWireframeSphere->SetWorld(worldBS);
	m_pWireframeSphere->SetColor(color);
	m_pWireframeSphere->Render(SceneManager::GetActiveCamera());
}

void Visualizer::privRenderAABB(Matrix& worldAABB, const Vect& color)
{
	m_pWireframeBox->SetWorld(worldAABB);
	m_pWireframeBox->SetColor(color);
	m_pWireframeBox->Render(SceneManager::GetActiveCamera());
}

void Visualizer::privRenderOBB(Matrix& worldOBB, const Vect& color)
{
	m_pWireframeBox->SetWorld(worldOBB);
	m_pWireframeBox->SetColor(color);
	m_pWireframeBox->Render(SceneManager::GetActiveCamera());
}
