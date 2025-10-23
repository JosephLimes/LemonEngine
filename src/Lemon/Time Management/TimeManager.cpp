#include "TimeManager.h"
#include "..\Lemon.h"
#include "FreezeTime.h"

TimeManager* TimeManager::m_pInstance;

TimeManager::TimeManager()
	:	m_currentTime(0.0f),
		m_frameTime(0.0f),
		m_previousTime(0.0f),
		m_pFreezeTime(new FreezeTime())
{}

TimeManager::~TimeManager()
{
	delete m_pFreezeTime;
}

TimeManager& TimeManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new TimeManager;
	}
	return *m_pInstance;
}

float TimeManager::GetTime()
{
	return Instance().m_currentTime;
}

float TimeManager::GetFrameTime()
{
	return Instance().m_frameTime;
}

void TimeManager::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void TimeManager::privProcessTime()
{
	m_previousTime = m_currentTime;

	m_currentTime = m_pFreezeTime->ComputeGameTime(m_previousTime);

	m_frameTime = m_currentTime - m_previousTime;
}
