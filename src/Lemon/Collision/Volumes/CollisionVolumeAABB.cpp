#include "CollisionVolumeAABB.h"

#include "CollisionVolumeBSphere.h"
#include "Tools/LemonMath.h"
#include "Tools/Visualizer/Visualizer.h"
#include "Tools/Colors.h"

CollisionVolumeAABB::CollisionVolumeAABB()
	: 
		m_world(Matrix(IDENTITY)),
		m_min(Vect()), 
		m_max(Vect()),
		m_scaleSqr(1.0f)
{}

CollisionVolumeAABB::CollisionVolumeAABB(Vect & min, Vect & max)
{
	m_min = min;
	m_max = max;

	// OBB data
	m_world = Matrix(IDENTITY);
	m_scaleSqr = 1.0f;
	SetOBBData();
}


const Matrix& CollisionVolumeAABB::GetWorld() const
{
	return m_world;
}

const Vect& CollisionVolumeAABB::GetMin() const
{
	return m_min;
}

const Vect& CollisionVolumeAABB::GetMax() const
{
	return m_max;
}

const Vect& CollisionVolumeAABB::GetHalfDiag() const
{
	return m_halfDiag;
}

const Vect& CollisionVolumeAABB::GetCenter() const
{
	return m_center;
}

const float CollisionVolumeAABB::GetScaleSqr() const
{
	return m_scaleSqr;
}

void CollisionVolumeAABB::Set(Vect& min, Vect& max)
{
	m_min = min;
	m_max = max;

	SetOBBData();
}

void CollisionVolumeAABB::DebugView(const Vect& color) const
{
	Visualizer::ShowAABB(*this, color);
}

void CollisionVolumeAABB::ComputeData(Model* pModel, const Matrix& mat)
{
	Vect currentVert;

	// grab model vertices
	Vect* array = pModel->getVectList();
	int vertCount = pModel->getVectNum();

	// initialize our values to the first vert
	currentVert = array[0] * mat;
	float minX = currentVert.X();
	float minY = currentVert.Y();
	float minZ = currentVert.Z();
	float maxX = currentVert.X();
	float maxY = currentVert.Y();
	float maxZ = currentVert.Z();
	
	// loop through remaining verts to find world min/max
	for (int i = 1; i < vertCount; i++)
	{
		currentVert = array[i] * mat;
		// check min vals
		if (currentVert.X() < minX) minX = currentVert.X();
		if (currentVert.Y() < minY) minY = currentVert.Y();
		if (currentVert.Z() < minZ) minZ = currentVert.Z();
		// check max vals
		if (currentVert.X() > maxX) maxX = currentVert.X();
		if (currentVert.Y() > maxY) maxY = currentVert.Y();
		if (currentVert.Z() > maxZ) maxZ = currentVert.Z();
	}

	// update points
	m_min.set(minX, minY, minZ);
	m_max.set(maxX, maxY, maxZ);

	SetOBBData();
}

void CollisionVolumeAABB::ComputeData(const CollisionVolumeBSphere& bSphere)
{
	Vect center = bSphere.GetCenter();
	float radius = bSphere.GetRadius();

	m_min.set(
		center.X() - radius,
		center.Y() - radius,
		center.Z() - radius
	);
	m_max.set(
		center.X() + radius,
		center.Y() + radius,
		center.Z() + radius
	);

	SetOBBData();
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectAccept(const Vect& point) const
{
	return LemonMath::Intersect(*this, point);
}

bool CollisionVolumeAABB::IntersectAccept(const Vect& point, const Vect& dir) const
{
	return LemonMath::Intersect(*this, point, dir);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return LemonMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return LemonMath::Intersect(*this, other);
}

void CollisionVolumeAABB::SetOBBData()
{
	m_halfDiag = (m_max - m_min) * 0.5f;
	m_center = (m_min + m_halfDiag);
}
