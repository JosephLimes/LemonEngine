#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	DrawableAttorney() = delete;
	DrawableAttorney(const DrawableAttorney&) = delete;
	DrawableAttorney& operator = (const DrawableAttorney&) = delete;
	~DrawableAttorney() = delete;

	class GameLoop
	{
	private:
		friend class		DrawableManager;
		friend class		EditorDrawableManager;
		static void			Draw2D(Drawable* pObj) { pObj->Draw2D(); };
		static void			Draw3D(Drawable* pObj) { pObj->Draw3D(); };
		static void			DrawEditor2D(Drawable* pObj) { pObj->DrawEditor2D(); }
		static void			DrawEditor3D(Drawable* pObj) { pObj->DrawEditor3D(); }
	};

	class Registration
	{
	private:
		friend class		DrawRegistrationCommand;
		friend class		DrawDeregistrationCommand;
		static void			Register(Drawable* pObj) { pObj->Register(); }
		static void			Deregister(Drawable* pObj) { pObj->Deregister(); }
	};
};

#endif _DrawableAttorney