#include "CollisionVolumeOBB.h"

#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"

CollisionVolumeOBB::CollisionVolumeOBB()
	: 
		m_world(Matrix()),
		m_min(Vect()), 
		m_max(Vect()),
		m_center(Vect()),
		m_halfDiag(Vect()),
		m_scaleSqr(-1.0f)
{}

const Matrix& CollisionVolumeOBB::GetWorld() const
{
	return m_world;
}

const Vect& CollisionVolumeOBB::GetMin() const
{
	return m_min;
}

const Vect& CollisionVolumeOBB::GetMax() const
{
	return m_max;
}

const Vect& CollisionVolumeOBB::GetHalfDiag() const
{
	return m_halfDiag;
}

const Vect& CollisionVolumeOBB::GetCenter() const
{
	return m_center;
}

const float CollisionVolumeOBB::GetScaleSqr() const
{
	return m_scaleSqr;
}

void CollisionVolumeOBB::DebugView(const Vect& color) const
{
	Visualizer::ShowOBB(*this, color);
}

void CollisionVolumeOBB::ComputeData(Model* pModel, const Matrix& mat)
{
	// local min and max
	m_min = pModel->getMinAABB();
	m_max = pModel->getMaxAABB();

	// world mat
	m_world = mat;

	// local half diagonal
	m_halfDiag = (m_max - m_min) * 0.5f;

	// world center
	m_center = (m_min + m_halfDiag) * m_world;

	// world squared scale factor
	m_scaleSqr = mat.get(ROW_0).magSqr();
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectAccept(const Vect& point) const
{
	return LemonMath::Intersect(*this, point);
}

bool CollisionVolumeOBB::IntersectAccept(const Vect& point, const Vect& dir) const
{
	return LemonMath::Intersect(*this, point, dir);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return LemonMath::Intersect(*this, other);
}
