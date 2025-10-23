#ifndef _LemonMath
#define _LemonMath

// Forward declarations
class Vect;
class Matrix;
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

namespace LemonMath
{
	bool					InRange(float a, float min, float max);															// if a is in range [min,max]
	bool					InRange(int a, int min, int max);																// if a is in range [min,max]
	bool					Overlap(float a, float b, float c, float d);													// overlap of intervals [a,b] and [c,d]
	CollisionVolumeAABB		AABBSum(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b);							// sum of two AABB's (AABB that encloses a and b)
	bool					OBBAxisOverlap(const Vect& axis, const CollisionVolumeOBB& a, const CollisionVolumeOBB& b);		// OBB helper function for testing single axis overlap
	bool					OBBAxisOverlap(const Vect& axis, const CollisionVolumeOBB& a, const CollisionVolumeAABB& b);	// OBB helper function for testing single axis overlap
	float					Clamp(float v, float min, float max);															// clamp v to min/max
	int						Clamp(int v, int min, int max);																	// clamp v to min/max
	bool					Intersect(const CollisionVolume& a, const CollisionVolume& b);									// generic volume -> generic volume
	bool					Intersect(const CollisionVolume& a, const Vect& b);												// generic volume -> point
	bool					Intersect(const CollisionVolume& a, const Vect& b, const Vect& v);								// generic volume -> ray

	// Bounding sphere collisions
	bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeBSphere& b);	// BSphere -> BSphere
	bool Intersect(const CollisionVolumeBSphere& a, const Vect& b);						// BSphere -> point
	bool Intersect(const CollisionVolumeBSphere& a, const Vect& b, const Vect& v);		// BSphere -> ray
	bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeAABB& b);		// BSphere -> AABB
	bool Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeOBB& b);		// BSphere -> OBB

	// Axis aligned bounding box collisions
	bool Intersect(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b);			// AABB -> AABB
	bool Intersect(const CollisionVolumeAABB& a, const Vect& b);						// AABB -> point
	bool Intersect(const CollisionVolumeAABB& a, const Vect& b, const Vect& v);			// AABB -> ray
	bool Intersect(const CollisionVolumeAABB& a, const CollisionVolumeBSphere& b);		// AABB -> BSphere
	bool Intersect(const CollisionVolumeAABB& a, const CollisionVolumeOBB& b);			// AABB -> OBB

	// Oriented bounding box collisions
	bool Intersect(const CollisionVolumeOBB& a, const CollisionVolumeOBB& b);			// OBB -> OBB
	bool Intersect(const CollisionVolumeOBB& a, const Vect& b);							// OBB -> point
	bool Intersect(const CollisionVolumeOBB& a, const Vect& b, const Vect& v);			// OBB -> ray
	bool Intersect(const CollisionVolumeOBB& a, const CollisionVolumeBSphere& b);		// OBB -> BSphere
	bool Intersect(const CollisionVolumeOBB& a, const CollisionVolumeAABB& b);			// OBB -> AABB
};

#endif _LemonMath