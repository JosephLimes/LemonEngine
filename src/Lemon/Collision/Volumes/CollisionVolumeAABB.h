#ifndef _CollisionVolumeAABB
#define _CollisionVolumeAABB

#include "AzulCore.h"
#include "CollisionVolume.h"

class CollisionVolumeAABB : public CollisionVolume
{
public:
	CollisionVolumeAABB();
	CollisionVolumeAABB(Vect& min, Vect& max);
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator = (const CollisionVolumeAABB&) = default;
	virtual ~CollisionVolumeAABB() = default;

private:
	Matrix			m_world; // identity, so OBB treats as local space
	Vect			m_min; // world space
	Vect			m_max; // world space
	Vect			m_halfDiag; // world space (TREATED AS LOCAL BY OBB)
	Vect			m_center; // world space
	float			m_scaleSqr;

public:

	// todo doc
	const Matrix&	GetWorld() const; // used by OBB, always identity
	const Vect&		GetMin() const;
	const Vect&		GetMax() const;
	const Vect&		GetHalfDiag() const;
	const Vect&		GetCenter() const;
	const float		GetScaleSqr() const; // used by OBB, always 1.0f

	void			Set(Vect& min, Vect& max);

	void			DebugView(const Vect& color) const override;

	void			ComputeData(Model* pModel, const Matrix& mat) override;
	void			ComputeData(const CollisionVolumeBSphere& bSphere);

	// doc later

	virtual bool	IntersectAccept(const CollisionVolume& other) const override;
	virtual bool	IntersectAccept(const Vect& point) const override;
	virtual bool	IntersectAccept(const Vect& point, const Vect& dir) const override;
	virtual bool	IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool	IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool	IntersectVisit(const CollisionVolumeOBB& other) const override;

private:
	void			SetOBBData();
};

#endif _CollisionVolumeAABB