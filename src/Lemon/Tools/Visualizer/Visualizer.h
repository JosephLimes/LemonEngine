#ifndef _Visualizer
#define _Visualizer

#include <stack>
#include <queue>

#include "AzulCore.h"
#include "../Colors.h"

class Command;
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class VisualizePointCommand;
class VisualizePointCommandPool;
class VisualizeSegmentCommand;
class VisualizeSegmentCommandPool;
class VisualizeBSphereCommand;
class VisualizeBSphereCommandPool;
class VisualizeAABBCommand;
class VisualizeAABBCommandPool;
class VisualizeOBBCommand;
class VisualizeOBBCommandPool;

class Visualizer : public Align16
{
	friend class VisualizerAttorney;

private:
	Visualizer();
	Visualizer(const Visualizer&) = delete;
	Visualizer operator = (const Visualizer&) = delete;
	~Visualizer();

	static Visualizer*						m_pInstance;

	static Vect								m_defaultColor;
	GraphicsObject_WireframeConstantColor*	m_pWireframeSphere;
	GraphicsObject_WireframeConstantColor*	m_pWireframeBox;

	// command pools (more to be added)
	VisualizePointCommandPool*				m_pointCommandPool;
	VisualizeSegmentCommandPool*			m_segmentCommandPool;
	VisualizeBSphereCommandPool*			m_bSphereCmdPool;
	VisualizeAABBCommandPool*				m_AABBCmdPool;
	VisualizeOBBCommandPool*				m_OBBCmdPool;

	// command queue
	std::queue<Command*>					m_cmdQueue;

	static Visualizer&						Instance();

public:
	static void								ShowPoint(const Vect& pos, const Vect& color = m_defaultColor);
	static void								ShowSegment(const Vect& pos1, const Vect& pos2, const Vect& color = m_defaultColor);
	static void								ShowCollisionVolume(const CollisionVolume& colVol, const Vect& color = m_defaultColor);
	static void								ShowBSphere(const CollisionVolumeBSphere& bSphere, const Vect& color = m_defaultColor);
	static void								ShowAABB(const CollisionVolumeAABB& aabb, const Vect& color = m_defaultColor);
	static void								ShowOBB(const CollisionVolumeOBB& obb, const Vect& color = m_defaultColor);

private:
	static void								Terminate();

	void									VisualizeAll();
	
	void									privRenderPoint(const Vect& pos, const Vect& color);
	void									privRenderSegment(const Vect& pos1, const Vect& pos2, const Vect& color);
	void									privRenderBSphere(Matrix& worldBS, const Vect& color);
	void									privRenderAABB(Matrix& worldAABB, const Vect& color);
	void									privRenderOBB(Matrix& worldOBB, const Vect& color);
};

#endif _Visualizer