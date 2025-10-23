#ifndef _CollisionVolumeOBB
#define _CollisionVolumeOBB

#include "AzulCore.h"
#include "CollisionVolume.h"

class CollisionVolumeOBB : public CollisionVolume
{
public:
	CollisionVolumeOBB();
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	CollisionVolumeOBB operator = (const CollisionVolumeOBB&) = delete;
	virtual ~CollisionVolumeOBB() = default;

private:
	Matrix			m_world;
	Vect			m_min; // model space
	Vect			m_max; // model space
	Vect			m_halfDiag; // model space
	Vect			m_center; // world space
	float			m_scaleSqr;

public:

	// todo doc
	const Matrix&	GetWorld() const;
	const Vect&		GetMin() const;
	const Vect&		GetMax() const;
	const Vect&		GetHalfDiag() const;
	const Vect&		GetCenter() const;
	const float		GetScaleSqr() const;

	void			DebugView(const Vect& color) const override;

	void			ComputeData(Model* pModel, const Matrix& mat) override;

	// doc later

	virtual bool	IntersectAccept(const CollisionVolume& other) const override;
	virtual bool	IntersectAccept(const Vect& point) const override;
	virtual bool	IntersectAccept(const Vect& point, const Vect& dir) const override;
	virtual bool	IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool	IntersectVisit(const CollisionVolumeAABB& other) const override;
	virtual bool	IntersectVisit(const CollisionVolumeOBB& other) const override;
};

#endif _CollisionVolumeOBB