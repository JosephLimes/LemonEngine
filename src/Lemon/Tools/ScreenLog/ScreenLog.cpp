#include "ScreenLog.h"
#include "ScreenLogSpriteStringPool.h"
#include "Sprite/SpriteString.h"
#include "Asset Management/FontManager.h"
#include "../Lemon.h"

ScreenLog* ScreenLog::m_pInstance;
char ScreenLog::m_charBuffer[256];

ScreenLog::ScreenLog()
	: 
		m_pFont(FontManager::Get("LEMON_DEFAULT_ARIAL")), 
		m_pStringPool(new ScreenLogSpriteStringPool()), 
		m_anchorX(0.0f), 
		m_anchorY(float(Lemon::GetHeight())),
		m_offsetY(0.0f)
{}

ScreenLog::~ScreenLog()
{
	// delete current strings
	for (SpriteString* pStr : m_messages)
	{
		delete pStr;
	}

	// delete recycled strings
	delete m_pStringPool;
}

ScreenLog& ScreenLog::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ScreenLog();
	}
	return *m_pInstance;
}

void ScreenLog::Add(char* pMsg, ...)
{
	// parse arguments to format string
	va_list args;

	va_start(args, pMsg);
	vsprintf_s(m_charBuffer, pMsg, args);
	va_end(args);

	std::string str(m_charBuffer);

	// add formatted string
	Instance().privAdd(str);
}

void ScreenLog::Edit(unsigned int line, char* pMsg, ...)
{
	assert(line < Instance().m_messages.size());

	// parse arguments to format string
	va_list args;

	va_start(args, pMsg);
	vsprintf_s(m_charBuffer, pMsg, args);
	va_end(args);

	std::string str(m_charBuffer);

	// edit formatted string
	Instance().privEdit(line, str);
}

void ScreenLog::Terminate()
{
	delete m_pInstance;
	m_pInstance = nullptr;
}

void ScreenLog::privRender()
{
	for (SpriteString* pString : m_messages)
	{
		pString->Render();
	}
}

void ScreenLog::privAdd(std::string str)
{
	SpriteString* pStr = m_pStringPool->GetSpriteString(m_pFont, str, m_anchorX, m_anchorY - m_offsetY);
	m_messages.push_back(pStr);
	m_offsetY += pStr->GetHeight();
}

void ScreenLog::privEdit(unsigned int line, std::string str)
{
	SpriteString* pOld = m_messages[line];
	SpriteString* pNew = m_pStringPool->GetSpriteString(m_pFont, str, m_anchorX, pOld->GetY());
	m_pStringPool->ReturnSpriteString(pOld);
	m_messages[line] = pNew;
}

void ScreenLog::privPop()
{
	if (!m_messages.empty())
	{
		SpriteString* pStr = m_messages.back();
		m_pStringPool->ReturnSpriteString(pStr);
		m_messages.pop_back();
		m_offsetY -= pStr->GetHeight();
	}
}

void ScreenLog::privClear()
{
	for (SpriteString* pStr : m_messages)
	{
		m_pStringPool->ReturnSpriteString(pStr);
	}
	m_messages.clear();
	m_offsetY = 0.0f;
}
