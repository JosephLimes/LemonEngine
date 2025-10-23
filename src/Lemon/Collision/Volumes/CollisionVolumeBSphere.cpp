#include "CollisionVolumeBSphere.h"

#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"

CollisionVolumeBSphere::CollisionVolumeBSphere()
	: m_radius(0.0f)
{}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return m_center;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return m_radius;
}

void CollisionVolumeBSphere::DebugView(const Vect& color) const
{
	Visualizer::ShowBSphere(*this, color);
}

void CollisionVolumeBSphere::ComputeData(Model* pModel, const Matrix& mat)
{
	// compute new center
	m_center = pModel->getCenter() * mat;

	// compute new radius
	Vect axis = Vect(mat[m0], mat[m1], mat[m2]);
	float length = axis.mag();
	m_radius = pModel->getRadius() * length;
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectAccept(const Vect& point) const
{
	return LemonMath::Intersect(*this, point);
}

bool CollisionVolumeBSphere::IntersectAccept(const Vect& point, const Vect& dir) const
{
	return LemonMath::Intersect(*this, point, dir);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return LemonMath::Intersect(*this, other);
}
