#include "..\Lemon.h"

//----------------------
// Called on game start 
//----------------------

void Lemon::GameInitialize()
{
	Lemon::SetWindowName("Tank Demo");
	Lemon::SetClear(0.6039f, 0.74117f, 0.96078f, 1.0f);


	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	Lemon::SetWidthHeight((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);  // 1/4 of the screen
	//this->SetWidthHeight(800, 600);  // set dimension directly
}