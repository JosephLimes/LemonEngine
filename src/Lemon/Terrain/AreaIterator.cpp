#include "AreaIterator.h"
#include "Terrain.h"
#include "Area.h"

AreaIterator::AreaIterator(const Area* pArea, Terrain::CellIndex cell)
	: m_pArea(pArea), m_cell(cell)
{}

bool AreaIterator::operator==(const AreaIterator& other)
{
	return	this->m_pArea == other.m_pArea &&
			this->m_cell == other.m_cell;
}

bool AreaIterator::operator!=(const AreaIterator& other)
{
	return	this->m_pArea != other.m_pArea ||
			this->m_cell != other.m_cell;
}

AreaIterator& AreaIterator::operator++()
{
	if (m_cell.j == m_pArea->end().m_cell.j)
	{
		// end of row, increment row and reset j to start of range
		m_cell.i++;
		m_cell.j = m_pArea->begin().m_cell.j;
	}
	else
	{
		// otherwise continue in this row
		m_cell.j++;
	}
	return *this;
}

AreaIterator AreaIterator::operator++(int)
{
	AreaIterator ret = *this;
	if (m_cell.j == m_pArea->end().m_cell.j)
	{
		// end of row, increment row and reset j to start of range
		m_cell.i++;
		m_cell.j = m_pArea->begin().m_cell.j;
	}
	else
	{
		// otherwise continue in this row
		m_cell.j++;
	}
	return ret;
}

AreaIterator& AreaIterator::operator--()
{
	if (m_cell.j == m_pArea->begin().m_cell.j)
	{
		// start of row, decrement row and reset j to end of range
		m_cell.i--;
		m_cell.j = m_pArea->end().m_cell.j;
	}
	else
	{
		// otherwise continue in this row
		m_cell.j--;
	}
	return *this;
}

AreaIterator AreaIterator::operator--(int)
{
	AreaIterator ret = *this;
	if (m_cell.j == m_pArea->begin().m_cell.j)
	{
		// start of row, decrement row and reset j to end of range
		m_cell.i--;
		m_cell.j = m_pArea->end().m_cell.j;
	}
	else
	{
		// otherwise continue in this row
		m_cell.j--;
	}
	return ret;
}

const CollisionVolumeAABB& AreaIterator::AABB() const
{
	return m_pArea->getTerrain()->CellAABB(m_cell);
}
