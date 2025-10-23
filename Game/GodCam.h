#ifndef _GodCam
#define _GodCam

#include "GameObject/GameObject.h"

class GodCam : public GameObject
{
public:
	GodCam();
	GodCam(const GodCam&) = delete;
	GodCam& operator = (const GodCam&) = delete;
	~GodCam();

private:
	Camera*			m_pCam;
	Matrix			m_rot;
	Vect			m_up;
	Vect			m_pos;
	Vect			m_dir;
	//const float		m_transSpeed = 1250.0f;
	const float		m_transSpeed = 200.0f;
	const float		m_rotSpeed = 0.03f;

public:
	void			Update() override;
	void			SetActive();

	void			KeyPressed(AZUL_KEY key) override;
};

#endif _GodCam