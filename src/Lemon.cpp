#include "AzulCore.h"

#include "Lemon.h"
#include "Asset Management\ModelManagerAttorney.h"
#include "Asset Management\ShaderManagerAttorney.h"
#include "Asset Management\TextureManagerAttorney.h"
#include "Asset Management\ImageManagerAttorney.h"
#include "Asset Management\FontManagerAttorney.h"
#include "Asset Management\TerrainManagerAttorney.h"
#include "Camera Management\CameraManager.h"
#include "Scene\SceneManagerAttorney.h"
#include "Time Management/TimeManagerAttorney.h"
#include "Tools/Visualizer/VisualizerAttorney.h"
#include "Tools/ScreenLog/ScreenLogAttorney.h"
#include "Tools/Editor/MapFileParserAttorney.h"
#include "Tools/Editor/LevelObjectManager.h"

Lemon* Lemon::m_pInstance;

Lemon& Lemon::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Lemon;
	}
	return *m_pInstance;
}

void Lemon::Initialize()
{
	// User defined setup
	GameInitialize();
}

void Lemon::LoadContent()
{
	LoadAllResources();
}

void Lemon::Update()
{
	TimeManagerAttorney::ProcessTime();
	SceneManagerAttorney::Update();
}

void Lemon::Draw()
{
	VisualizerAttorney::VisualizeAll();
	SceneManagerAttorney::Draw();
	ScreenLogAttorney::Render();
}

void Lemon::UnLoadContent()
{
	ModelManagerAttorney::Terminate();
	ShaderManagerAttorney::Terminate();
	TextureManagerAttorney::Terminate();
	ImageManagerAttorney::Terminate();
	FontManagerAttorney::Terminate();
	TerrainManagerAttorney::Terminate();
	SceneManagerAttorney::Terminate();
	TimeManagerAttorney::Terminate();
	VisualizerAttorney::Terminate();
	ScreenLogAttorney::Terminate();
	MapFileParserAttorney::Terminate();
	LevelObjectManager::Terminate();
}

void Lemon::privRun()
{
	// call azul run
	run();
	// clean up when finished
	Terminate();
}

float Lemon::GetTime()
{
	return Instance().GetTimeInSeconds();
}

// get screen height
int Lemon::GetHeight()
{
	return Instance().getHeight();
}

// get screen width
int Lemon::GetWidth()
{
	return Instance().getWidth();
}

void Lemon::SetWidthHeight(int width, int height)
{
	Instance().setWidthHeight(width, height);
}

// set background color
void Lemon::SetClear(float r, float g, float b, float a)
{
	Instance().SetClearColor(r, g, b, a);
}

void Lemon::SetWindowName(const char* name)
{
	Instance().setWindowName(name);
}

void Lemon::onKey(int key, int action)
{
	if (action == 1)
	{
		SceneManagerAttorney::QueueInput(key);
	}
}

void Lemon::Terminate()
{
	Instance().GameTerminate();
	delete m_pInstance;
}