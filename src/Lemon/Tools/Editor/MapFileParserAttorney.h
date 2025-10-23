#ifndef _MapFileParserAttorney
#define _MapFileParserAttorney

#include "MapFileParser.h"

class MapFileParserAttorney
{
public:
	friend class Lemon;

	MapFileParserAttorney() = delete;
	MapFileParserAttorney(const MapFileParserAttorney&) = delete;
	MapFileParserAttorney& operator = (const MapFileParserAttorney&) = delete;
	~MapFileParserAttorney() = delete;

private:
	// passthrough for engine
	static void			Terminate() { MapFileParser::Terminate(); }
};

#endif _MapFileParserAttorney