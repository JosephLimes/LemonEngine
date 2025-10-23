#include "Area.h"

Area::Area(const Terrain* pTerrain, Terrain::CellIndex begin, Terrain::CellIndex end)
	: m_pTerrain(pTerrain), m_begin(AreaIterator(this, begin)), m_end(AreaIterator(this, end))
{}

const AreaIterator& Area::begin() const
{
	return m_begin;
}

const AreaIterator& Area::end() const
{
	return m_end;
}

const Terrain* Area::getTerrain() const
{
	return m_pTerrain;
}
