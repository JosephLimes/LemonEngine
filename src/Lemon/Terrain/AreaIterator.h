#ifndef _AreaIterator
#define _AreaIterator

#include "Terrain.h"

class CollisionVolumeAABB;

class AreaIterator
{
public:
	AreaIterator(const Area* pArea, Terrain::CellIndex cell);
	AreaIterator() = delete;
	AreaIterator(const AreaIterator&) = default;
	AreaIterator& operator = (const AreaIterator&) = default;
	~AreaIterator() = default;

private:
	const Area*					m_pArea;
	Terrain::CellIndex			m_cell;

public:
	// operator overloads
	bool						operator==(const AreaIterator& other);
	bool						operator!=(const AreaIterator& other);
	AreaIterator&				operator++();		// prefix
	AreaIterator				operator++(int);	// postfix
	AreaIterator&				operator--();		// prefix
	AreaIterator				operator--(int);	// postfix

	// Volume accessor
	const CollisionVolumeAABB&	AABB() const;
};

#endif _AreaIterator