#ifndef _DebugController
#define _DebugController

#include "GameObject/GameObject.h"

class GodCam;
class Sprite;
class SpriteFont;
class SpriteString;

class DebugController : public GameObject
{
public:
	DebugController();
	DebugController(const DebugController&) = delete;
	DebugController& operator = (const DebugController&) = delete;
	~DebugController();

private:
	GodCam*				m_pGodCam;
	int					m_frameCount;
	bool				m_vsync;

public:
	void				KeyPressed(AZUL_KEY key) override;
	void				Update() override;
	void				Alarm0() override;
};

#endif _DebugController