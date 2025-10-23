#ifndef _Area
#define _Area

#include "AreaIterator.h"
#include "Terrain.h"

class Area
{
public:
	Area(const Terrain* pTerrain, Terrain::CellIndex begin, Terrain::CellIndex end);
	Area() = delete;
	Area(const Area&) = default;
	Area& operator = (const Area&) = default;
	~Area() = default;

private:
	const Terrain*		m_pTerrain;
	AreaIterator		m_begin;
	AreaIterator		m_end;

public:
	const AreaIterator&	begin() const;
	const AreaIterator& end() const;
	const Terrain* getTerrain() const;
};

#endif _Area