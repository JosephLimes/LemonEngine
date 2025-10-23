#ifndef _CollisionVolumeBSphere
#define _CollisionVolumeBSphere

#include "AzulCore.h"
#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere operator = (const CollisionVolumeBSphere&) = delete;
	virtual ~CollisionVolumeBSphere() = default;

private:
	Vect			m_center;
	float			m_radius;

public:

	const Vect&		GetCenter() const;


	float			GetRadius() const;

	// doc later

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

#endif _CollisionVolumeBSphere