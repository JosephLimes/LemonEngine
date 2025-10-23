#ifndef _ScreenLog
#define _ScreenLog

#include <vector>

class ScreenLogSpriteStringPool;
class SpriteFont;
class SpriteString;

class ScreenLog
{
	friend class ScreenLogAttorney;

private:
	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog& operator = (const ScreenLog&) = delete;
	~ScreenLog();

	static ScreenLog*			m_pInstance;

	SpriteFont*					m_pFont;
	static char					m_charBuffer[256];
	float						m_anchorX;
	float						m_anchorY;
	float						m_offsetY; // to correctly place new added strings
	std::vector<SpriteString*>	m_messages;
	ScreenLogSpriteStringPool*	m_pStringPool;

	static ScreenLog&			Instance();

public:
	static void					Render() { Instance().privRender(); };

	static void					Add(char* pMsg, ...);
	static void					Edit(unsigned int line, char* pMsg, ...);
	static void					Pop() { Instance().privPop(); }
	static void					Clear() { Instance().privClear(); };

private:
	static void					Terminate();

	void						privRender();
	void						privAdd(std::string str);
	void						privEdit(unsigned int line, std::string str);
	void						privPop();
	void						privClear();

};

#endif _ScreenLog