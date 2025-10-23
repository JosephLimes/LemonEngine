#ifndef _VisualizerAttorney
#define _VisualizerAttorney

#include "AzulCore.h"

#include "Visualizer.h"
#include "VisualizePointCommandPool.h"
#include "VisualizeSegmentCommandPool.h"
#include "VisualizeBSphereCommandPool.h"
#include "VisualizeAABBCommandPool.h"
#include "VisualizeOBBCommandPool.h"

class VisualizerAttorney
{
public:
	friend class Lemon;
	friend class VisualizePointCommand;
	friend class VisualizeSegmentCommand;
	friend class VisualizeBSphereCommand;
	friend class VisualizeAABBCommand;
	friend class VisualizeOBBCommand;

	VisualizerAttorney() = delete;
	VisualizerAttorney(const VisualizerAttorney&) = delete;
	VisualizerAttorney& operator = (const VisualizerAttorney&) = delete;
	~VisualizerAttorney() = delete;

private:
	// passthrough for engine
	static void					Terminate() { Visualizer::Terminate(); }
	static void					VisualizeAll() { Visualizer::Instance().VisualizeAll(); }

	// passthroughs for point command
	static void					RenderPoint(const Vect& pos, const Vect& color) { Visualizer::Instance().privRenderPoint(pos, color); }
	static void					RecycleCmd(VisualizePointCommand* pCmd) { Visualizer::Instance().m_pointCommandPool->RecycleCommand(pCmd); }

	// passthroughs for segment command
	static void					RenderSegment(const Vect& pos1, const Vect& pos2, const Vect& color) { Visualizer::Instance().privRenderSegment(pos1, pos2, color); }
	static void					RecycleCmd(VisualizeSegmentCommand* pCmd) { Visualizer::Instance().m_segmentCommandPool->RecycleCommand(pCmd); }

	// passthroughs for BSphere command
	static void					RenderBSphere(Matrix& worldBS, const Vect& color) { Visualizer::Instance().privRenderBSphere(worldBS, color); };
	static void					RecycleCmd(VisualizeBSphereCommand* pCmd) { Visualizer::Instance().m_bSphereCmdPool->RecycleCommand(pCmd); };

	// passthroughs for AABB command
	static void					RenderAABB(Matrix& worldAABB, const Vect& color) { Visualizer::Instance().privRenderAABB(worldAABB, color); };
	static void					RecycleCmd(VisualizeAABBCommand* pCmd) { Visualizer::Instance().m_AABBCmdPool->RecycleCommand(pCmd); };

	// passthroughs for OBB command
	static void					RenderOBB(Matrix& worldOBB, const Vect& color) { Visualizer::Instance().privRenderOBB(worldOBB, color); };
	static void					RecycleCmd(VisualizeOBBCommand* pCmd) { Visualizer::Instance().m_OBBCmdPool->RecycleCommand(pCmd); }
};

#endif _VisualizerAttorney