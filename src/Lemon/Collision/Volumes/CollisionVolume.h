#ifndef _CollisionVolume
#define _CollisionVolume

class Model;
class Matrix;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume
{
public:
	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = default;
	CollisionVolume& operator = (const CollisionVolume&) = default;
	virtual ~CollisionVolume() = default;


	virtual void		DebugView(const Vect& color) const = 0;

	virtual void		ComputeData(Model* pModel, const Matrix& world) = 0;

	virtual bool		IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool		IntersectAccept(const Vect& point) const = 0;
	virtual bool		IntersectAccept(const Vect& point, const Vect& dir) const = 0;
	virtual bool		IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool		IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool		IntersectVisit(const CollisionVolumeOBB& other) const = 0;
};

#endif _CollisionVolume