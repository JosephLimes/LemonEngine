#include "EditorInputCamera.h"
#include "EditorAdmin.h"

EditorInputCamera::EditorInputCamera(EditorAdmin* pAdmin)
{
	this->m_pAdmin = pAdmin;
}

void EditorInputCamera::ProcessInputs()
{
	m_pAdmin->ProcessCameraInput();
}
