#include "ScreenLogSpriteStringPool.h"
#include "Sprite/SpriteString.h"

SpriteString* ScreenLogSpriteStringPool::GetSpriteString(SpriteFont* pFont, std::string string, float x, float y)
{
	SpriteString* pStr;

	if (recycledItems.empty())
	{
		pStr = new SpriteString(pFont, string, x, y);
	}
	else
	{
		pStr = recycledItems.top();
		recycledItems.pop();
		pStr->Set(pFont, string, x, y);
	}

	return pStr;
}

void ScreenLogSpriteStringPool::ReturnSpriteString(SpriteString* b)
{
	recycledItems.push(static_cast<SpriteString*>(b));
}

ScreenLogSpriteStringPool::~ScreenLogSpriteStringPool()
{
	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}