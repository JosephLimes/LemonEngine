#include "DebugController.h"
#include "../Lemon.h"
#include "GodCam.h"
#include "Sprite/Sprite.h"
#include "Asset Management/ImageManager.h"
#include "Asset Management/FontManager.h"
#include "Sprite/SpriteFont.h"
#include "Sprite/SpriteString.h"
#include "Tools/ScreenLog/ScreenLog.h"
#include "Time Management/TimeManager.h"

DebugController::DebugController()
	: m_pGodCam(new GodCam()), m_frameCount(0), m_vsync(true)
{
	// update fps display
	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 0.5f);

	Inputable::SubmitRegistration(AZUL_KEY::KEY_F1, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F2, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F3, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F4, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_F5, KeyEvent::KEY_PRESS);
	Inputable::SubmitRegistration(AZUL_KEY::KEY_V, KeyEvent::KEY_PRESS);

	Updatable::SubmitRegistration();
}

DebugController::~DebugController()
{
	delete m_pGodCam;
}

void DebugController::KeyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_F1:
		m_pGodCam->SetActive();
		break;
	case AZUL_KEY::KEY_F2:
		ScreenLog::Add("Testing hello :)");
		break;
	case AZUL_KEY::KEY_F3:
		SceneManager::SetInputMode(InputMode::TYPED);
		break;
	case AZUL_KEY::KEY_F4:
		ScreenLog::Pop();
		break;
	case AZUL_KEY::KEY_F5:
		ScreenLog::Clear();
		break;
	case AZUL_KEY::KEY_V:
		if (m_vsync)
		{
			//Lemon::Instance().setVsync(false);
			m_vsync = false;
		}
		else
		{
			//Lemon::Instance().setVsync(true);
			m_vsync = true;
		}
		break;
	}
}

void DebugController::Update()
{
	m_frameCount++;
}

void DebugController::Alarm0()
{
	// simple fps counter, updates twice per second
	ScreenLog::Clear();
	ScreenLog::Add("FPS: %d", m_frameCount * 2);
	m_frameCount = 0;

	Alarmable::SubmitRegistration(AlarmableManager::AlarmID::ALARM_0, 0.5f);
}
