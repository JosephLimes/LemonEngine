#ifndef _ScreenLogSpriteStringPool
#define _ScreenLogSpriteStringPool

#include <stack>

class SpriteFont;
class SpriteString;

class ScreenLogSpriteStringPool
{
public:
	ScreenLogSpriteStringPool() = default;
	ScreenLogSpriteStringPool(const ScreenLogSpriteStringPool&) = delete;
	ScreenLogSpriteStringPool& operator=(const ScreenLogSpriteStringPool&) = delete;
	~ScreenLogSpriteStringPool();

private:
	std::stack<SpriteString*>	recycledItems;

public:
	SpriteString*				GetSpriteString(SpriteFont* pFont, std::string string, float x, float y);
	void						ReturnSpriteString(SpriteString* pStr);
};

#endif _ScreenLogSpriteStringPool