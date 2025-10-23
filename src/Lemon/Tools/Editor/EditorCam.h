#ifndef _EditorCam
#define _EditorCam

#include "AzulCore.h"

class EditorAdmin;

class EditorCam
{
public:
	EditorCam(EditorAdmin* pAdmin);
	EditorCam() = delete;
	EditorCam(const EditorCam&) = delete;
	EditorCam& operator = (const EditorCam&) = delete;
	virtual ~EditorCam();

	void			ProcessInputs();
	Matrix			GetProjMatrix();
	Matrix			GetViewMatrix();

private:
	EditorAdmin*	m_pAdmin;
	Camera*			m_pCam;
	Matrix			m_camrot;
	Vect			m_camup;
	Vect			m_campos;
	Vect			m_camdir;
	const float		m_transSpeed = 500.0f;
	const float		m_rotSpeed = 1.0f;
};

#endif _EditorCam