#ifndef LEMON_H
#define LEMON_H

#include "AzulCore.h"

class Lemon: public Engine
{
private:
	friend class LemonAttorney;

	Lemon() = default;
	Lemon(const Lemon&) = delete;
	Lemon& operator = (const Lemon&) = delete;
	~Lemon() = default;

	static Lemon*			m_pInstance;

	static Lemon&			Instance();

	// Azul functions
    virtual void			Initialize();
    virtual void			LoadContent();
	virtual void			Update();
    virtual void			Draw();
    virtual void			UnLoadContent();

	// Gameloop (called by main)
	void					privRun();

	// User defined
	void					LoadAllResources();
	void					GameInitialize();
	void					GameTerminate();

	// For use by time manager
	static float			GetTime();
public:
	// window services
	static int				GetHeight();
	static int				GetWidth();
	static void				SetWidthHeight(int width, int height);
	static void				SetClear(float r, float g, float b, float a);
	static void				SetWindowName(const char* name);

	// for typed input
	virtual void			onKey(int key, int action) override;

	// Game loop
	static void				Run() { Instance().privRun(); };
	static void				Terminate();
};

#endif