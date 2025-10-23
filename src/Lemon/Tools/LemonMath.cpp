#include "LemonMath.h"

#include "AzulCore.h"

#include "Collision/Volumes/CollisionVolumeBSphere.h"
#include "Collision/Volumes/CollisionVolumeAABB.h"
#include "Collision/Volumes/CollisionVolumeOBB.h"

#include "Tools/Visualizer/Visualizer.h"

bool LemonMath::InRange(float a, float min, float max)
{
	return a >= min && a <= max;
}

bool LemonMath::InRange(int a, int min, int max)
{
	return a >= min && a <= max;
}

bool LemonMath::Overlap(float a, float b, float c, float d)
{
	if (b < c || d < a) return false;
	return true;
}

CollisionVolumeAABB LemonMath::AABBSum(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b)
{
	Vect min;
	Vect max;
	Vect aMin = a.GetMin();
	Vect aMax = a.GetMax();
	Vect bMin = b.GetMin();
	Vect bMax = b.GetMax();
	
	min.set(
		std::min(aMin.X(), bMin.X()),
		std::min(aMin.Y(), bMin.Y()),
		std::min(aMin.Z(), bMin.Z())
	);
	max.set(
		std::max(aMax.X(), bMax.X()),
		std::max(aMax.Y(), bMax.Y()),
		std::max(aMax.Z(), bMax.Z())
	);

	return CollisionVolumeAABB(min, max);
}

bool LemonMath::OBBAxisOverlap(const Vect& axis, const CollisionVolumeOBB& a, const CollisionVolumeOBB& b)
{
	float axisLenSqr = axis.magSqr();
	if (axisLenSqr < FLT_EPSILON) return true;

	float d = (
		abs((a.GetCenter() - b.GetCenter()).dot(axis)) / 
		axisLenSqr
		);
	
	Vect aD = a.GetHalfDiag();
	Vect axisA = axis * a.GetWorld().getInv();
	float pA = (
		(
		abs(axisA.X() * aD.X()) +
		abs(axisA.Y() * aD.Y()) +
		abs(axisA.Z() * aD.Z())
		) / axisLenSqr
		);
	pA *= a.GetScaleSqr();

	Vect bD = b.GetHalfDiag();
	Vect axisB = axis * b.GetWorld().getInv();
	float pB = (
		(
		abs(axisB.X() * bD.X()) +
		abs(axisB.Y() * bD.Y()) +
		abs(axisB.Z() * bD.Z())
		) / axisLenSqr
		);
	pB *= b.GetScaleSqr();

	return d <= pA + pB;
}

bool LemonMath::OBBAxisOverlap(const Vect& axis, const CollisionVolumeOBB& a, const CollisionVolumeAABB& b)
{
	float axisLenSqr = axis.magSqr();
	if (axisLenSqr < FLT_EPSILON) return true;

	float d = (
		abs((a.GetCenter() - b.GetCenter()).dot(axis)) /
		axisLenSqr
		);

	Vect aD = a.GetHalfDiag();
	Vect axisA = axis * a.GetWorld().getInv();
	float pA = (
		(
			abs(axisA.X() * aD.X()) +
			abs(axisA.Y() * aD.Y()) +
			abs(axisA.Z() * aD.Z())
			) / axisLenSqr
		);
	pA *= a.GetScaleSqr();

	Vect bD = b.GetHalfDiag();
	Vect axisB = axis * b.GetWorld().getInv();
	float pB = (
		(
			abs(axisB.X() * bD.X()) +
			abs(axisB.Y() * bD.Y()) +
			abs(axisB.Z() * bD.Z())
			) / axisLenSqr
		);
	pB *= b.GetScaleSqr();

	return d <= pA + pB;
}

float LemonMath::Clamp(float v, float min, float max)
{
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

int LemonMath::Clamp(int v, int min, int max)
{
	if (v < min) return min;
	if (v > max) return max;
	return v;
}

bool LemonMath::Intersect(const CollisionVolume& a, const CollisionVolume& b)
{
	return a.IntersectAccept(b);
}

bool LemonMath::Intersect(const CollisionVolume& a, const Vect& b)
{
	return a.IntersectAccept(b);
}

bool LemonMath::Intersect(const CollisionVolume& a, const Vect& b, const Vect& v)
{
	return a.IntersectAccept(b, v);
}

bool LemonMath::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeBSphere& b)
{
	// get squared length of the vector from a to b
	float distSqr = (a.GetCenter() - b.GetCenter()).magSqr();
	// get squared sum of the radii
	float radiiSqr = a.GetRadius() + b.GetRadius();
	radiiSqr *= radiiSqr;
	// determine if there is intersection
	return distSqr < radiiSqr;
}

bool LemonMath::Intersect(const CollisionVolumeBSphere& a, const Vect& b)
{
	// get squared length of the vector from a (center) to b
	float distSqr = (a.GetCenter() - b).magSqr();
	
	// if distance from a to b is less or equal to radius, point is within the BSphere
	if (distSqr <= a.GetRadius() * a.GetRadius()) return true;
	return false;
}

bool LemonMath::Intersect(const CollisionVolumeBSphere& a, const Vect& b, const Vect& v)
{
	// vector between bsphere origin and ray origin
	Vect w = a.GetCenter() - b;
	float wSqr = w.dot(w);
	float proj = w.dot(v);
	float rSqr = a.GetRadius() * a.GetRadius();

	// if sphere is beind ray, no intersection
	if (proj < 0.0f && wSqr > rSqr) return false;

	float vSqr = v.dot(v);

	// compare length of difference vs radius
	return (vSqr * wSqr - proj * proj <= vSqr * rSqr);
}

bool LemonMath::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeAABB& b)
{
	Vect v = a.GetCenter();
	Vect min = b.GetMin();
	Vect max = b.GetMax();

	// clamp BSphere center to AABB's min/max
	v.set(
		Clamp(v.X(), min.X(), max.X()),
		Clamp(v.Y(), min.Y(), max.Y()),
		Clamp(v.Z(), min.Z(), max.Z())
	);

	// determine if clamped point is within the BSphere
	return Intersect(a, v);
}

bool LemonMath::Intersect(const CollisionVolumeBSphere& a, const CollisionVolumeOBB& b)
{
	// compute BSphere center in local space
	Vect point = a.GetCenter() * b.GetWorld().getInv();

	// clamp to local OBB
	Vect min = b.GetMin();
	Vect max = b.GetMax();
	point.set(
		Clamp(point.X(), min.X(), max.X()),
		Clamp(point.Y(), min.Y(), max.Y()),
		Clamp(point.Z(), min.Z(), max.Z())
	);

	// move back to world space
	point = point * b.GetWorld();

	// determine if world point is inside BSphere
	return Intersect(a, point);
}

bool LemonMath::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeAABB& b)
{
	Vect aMin = a.GetMin();
	Vect aMax = a.GetMax();
	Vect bMin = b.GetMin();
	Vect bMax = b.GetMax();
	// test each axis to ensure they all overlap
	if (!Overlap(aMin.X(), aMax.X(), bMin.X(), bMax.X())) return false;
	if (!Overlap(aMin.Y(), aMax.Y(), bMin.Y(), bMax.Y())) return false;
	if (!Overlap(aMin.Z(), aMax.Z(), bMin.Z(), bMax.Z())) return false;
	return true;
}

bool LemonMath::Intersect(const CollisionVolumeAABB& a, const Vect& b)
{
	Vect min = a.GetMin();
	Vect max = a.GetMax();
	// test each axis to ensure point is within each interval
	if (b.X() < min.X() || b.X() > max.X()) return false;
	if (b.Y() < min.Y() || b.Y() > max.Y()) return false;
	if (b.Z() < min.Z() || b.Z() > max.Z()) return false;
	return true;
}

bool LemonMath::Intersect(const CollisionVolumeAABB& a, const Vect& b, const Vect& v)
{
	Vect vInv = Vect(1.0f / v.X(), 1.0f / v.Y(), 1.0f / v.Z());

	float tx1 = (a.GetMin().X() - b.X()) * vInv.X();
	float tx2 = (a.GetMax().X() - b.X()) * vInv.X();

	float tmin = std::min(tx1, tx2);
	float tmax = std::max(tx1, tx2);

	float ty1 = (a.GetMin().Y() - b.Y()) * vInv.Y();
	float ty2 = (a.GetMax().Y() - b.Y()) * vInv.Y();

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	float tz1 = (a.GetMin().Z() - b.Z()) * vInv.Z();
	float tz2 = (a.GetMax().Z() - b.Z()) * vInv.Z();

	tmin = std::max(tmin, std::min(tz1, tz2));
	tmax = std::min(tmax, std::max(tz1, tz2));

	return tmax >= tmin;
}

bool LemonMath::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeBSphere& b)
{
	Vect v = b.GetCenter();
	Vect min = a.GetMin();
	Vect max = a.GetMax();

	// clamp BSphere center to AABB's min/max
	v.set(
		Clamp(v.X(), min.X(), max.X()),
		Clamp(v.Y(), min.Y(), max.Y()),
		Clamp(v.Z(), min.Z(), max.Z())
	);

	// determine if clamped point is within the BSphere
	return Intersect(b, v);
}

bool LemonMath::Intersect(const CollisionVolumeAABB& a, const CollisionVolumeOBB& b)
{
	// test each of the 15 potential axes, if any do not overlap there is no intersection
	Vect bX = b.GetWorld().get(ROW_0);
	if (!OBBAxisOverlap(bX, b, a)) return false;

	Vect bY = b.GetWorld().get(ROW_1);
	if (!OBBAxisOverlap(bY, b, a)) return false;

	Vect bZ = b.GetWorld().get(ROW_2);
	if (!OBBAxisOverlap(bZ, b, a)) return false;

	Vect aX = Vect(1.0f, 0.0f, 0.0f, 0.0f);
	if (!OBBAxisOverlap(aX, b, a)) return false;

	Vect aY = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	if (!OBBAxisOverlap(aY, b, a)) return false;

	Vect aZ = Vect(0.0f, 0.0f, 1.0f, 0.0f);
	if (!OBBAxisOverlap(aZ, b, a)) return false;

	Vect bXaX = bX.cross(aX);
	if (!OBBAxisOverlap(bXaX, b, a)) return false;

	Vect bYaX = bY.cross(aX);
	if (!OBBAxisOverlap(bYaX, b, a)) return false;

	Vect bZaX = bZ.cross(aX);
	if (!OBBAxisOverlap(bZaX, b, a)) return false;

	Vect bXaY = bX.cross(aY);
	if (!OBBAxisOverlap(bXaY, b, a)) return false;

	Vect bYaY = bY.cross(bY);
	if (!OBBAxisOverlap(bYaY, b, a)) return false;

	Vect bZaY = bZ.cross(bY);
	if (!OBBAxisOverlap(bZaY, b, a)) return false;

	Vect bXaZ = bX.cross(bZ);
	if (!OBBAxisOverlap(bXaZ, b, a)) return false;

	Vect bYaZ = bY.cross(bZ);
	if (!OBBAxisOverlap(bYaZ, b, a)) return false;

	Vect bZaZ = bZ.cross(bZ);
	if (!OBBAxisOverlap(bZaZ, b, a)) return false;

	// all axes overlap
	return true;
}

bool LemonMath::Intersect(const CollisionVolumeOBB& a, const CollisionVolumeOBB& b)
{
	// test each of the 15 potential axes, if any do not overlap there is no intersection
	Vect aX = a.GetWorld().get(ROW_0);
	if (!OBBAxisOverlap(aX, a, b)) return false;

	Vect aY = a.GetWorld().get(ROW_1);
	if (!OBBAxisOverlap(aY, a, b)) return false;

	Vect aZ = a.GetWorld().get(ROW_2);
	if (!OBBAxisOverlap(aZ, a, b)) return false;

	Vect bX = b.GetWorld().get(ROW_0);
	if (!OBBAxisOverlap(bX, a, b)) return false;

	Vect bY = b.GetWorld().get(ROW_1);
	if (!OBBAxisOverlap(bY, a, b)) return false;

	Vect bZ = b.GetWorld().get(ROW_2);
	if (!OBBAxisOverlap(bZ, a, b)) return false;

	Vect aXbX = aX.cross(bX);
	if (!OBBAxisOverlap(aXbX, a, b)) return false;

	Vect aYbX = aY.cross(bX);
	if (!OBBAxisOverlap(aYbX, a, b)) return false;

	Vect aZbX = aZ.cross(bX);
	if (!OBBAxisOverlap(aZbX, a, b)) return false;

	Vect aXbY = aX.cross(bY);
	if (!OBBAxisOverlap(aXbY, a, b)) return false;

	Vect aYbY = aY.cross(bY);
	if (!OBBAxisOverlap(aYbY, a, b)) return false;

	Vect aZbY = aZ.cross(bY);
	if (!OBBAxisOverlap(aZbY, a, b)) return false;

	Vect aXbZ = aX.cross(bZ);
	if (!OBBAxisOverlap(aXbZ, a, b)) return false;

	Vect aYbZ = aY.cross(bZ);
	if (!OBBAxisOverlap(aYbZ, a, b)) return false;

	Vect aZbZ = aZ.cross(bZ);
	if (!OBBAxisOverlap(aZbZ, a, b)) return false;

	// all axes overlap
	return true;
}

bool LemonMath::Intersect(const CollisionVolumeOBB& a, const Vect& b)
{
	// transform point b to obb local space
	Vect point = b * a.GetWorld().getInv();

	// test like an AABB in local space
	Vect min = a.GetMin();
	Vect max = a.GetMax();
	// test each axis to ensure point is within each interval
	if (b.X() < min.X() || b.X() > max.X()) return false;
	if (b.Y() < min.Y() || b.Y() > max.Y()) return false;
	if (b.Z() < min.Z() || b.Z() > max.Z()) return false;
	return true;
}

bool LemonMath::Intersect(const CollisionVolumeOBB& a, const Vect& b, const Vect& v)
{
	a, b, v;
	return true;
	// fix

	//// transform ray to local space
	//Vect lb = b * a.GetWorld().getInv();
	//Vect vInv = v * a.GetWorld().getInv();
	//vInv = Vect(1.0f / vInv.X(), 1.0f / vInv.Y(), 1.0f / vInv.Z());

	//float tx1 = (a.GetMin().X() - lb.X()) * vInv.X();
	//float tx2 = (a.GetMax().X() - lb.X()) * vInv.X();

	//float tmin = std::min(tx1, tx2);
	//float tmax = std::max(tx1, tx2);

	//float ty1 = (a.GetMin().Y() - lb.Y()) * vInv.Y();
	//float ty2 = (a.GetMax().Y() - lb.Y()) * vInv.Y();

	//tmin = std::max(tmin, std::min(ty1, ty2));
	//tmax = std::min(tmax, std::max(ty1, ty2));

	//float tz1 = (a.GetMin().Z() - lb.Z()) * vInv.Z();
	//float tz2 = (a.GetMax().Z() - lb.Z()) * vInv.Z();

	//tmin = std::max(tmin, std::min(tz1, tz2));
	//tmax = std::min(tmax, std::max(tz1, tz2));

	//return tmax >= tmin;
}

bool LemonMath::Intersect(const CollisionVolumeOBB& a, const CollisionVolumeBSphere& b)
{
	// compute BSphere center in local space
	Vect point = b.GetCenter() * a.GetWorld().getInv();

	// clamp to local OBB
	Vect min = a.GetMin();
	Vect max = a.GetMax();
	point.set(
		Clamp(point.X(), min.X(), max.X()),
		Clamp(point.Y(), min.Y(), max.Y()),
		Clamp(point.Z(), min.Z(), max.Z())
	);

	// move back to world space
	point = point * a.GetWorld();

	// determine if world point is inside BSphere
	return Intersect(b, point);
}

bool LemonMath::Intersect(const CollisionVolumeOBB& a, const CollisionVolumeAABB& b)
{
	// test each of the 15 potential axes, if any do not overlap there is no intersection
	Vect aX = a.GetWorld().get(ROW_0);
	if (!OBBAxisOverlap(aX, a, b)) return false;

	Vect aY = a.GetWorld().get(ROW_1);
	if (!OBBAxisOverlap(aY, a, b)) return false;

	Vect aZ = a.GetWorld().get(ROW_2);
	if (!OBBAxisOverlap(aZ, a, b)) return false;

	Vect bX = Vect(1.0f ,0.0f, 0.0f, 0.0f);
	if (!OBBAxisOverlap(bX, a, b)) return false;

	Vect bY = Vect(0.0f, 1.0f, 0.0f, 0.0f);
	if (!OBBAxisOverlap(bY, a, b)) return false;

	Vect bZ = Vect(0.0f, 0.0f, 1.0f, 0.0f);
	if (!OBBAxisOverlap(bZ, a, b)) return false;

	Vect aXbX = aX.cross(bX);
	if (!OBBAxisOverlap(aXbX, a, b)) return false;

	Vect aYbX = aY.cross(bX);
	if (!OBBAxisOverlap(aYbX, a, b)) return false;

	Vect aZbX = aZ.cross(bX);
	if (!OBBAxisOverlap(aZbX, a, b)) return false;

	Vect aXbY = aX.cross(bY);
	if (!OBBAxisOverlap(aXbY, a, b)) return false;

	Vect aYbY = aY.cross(bY);
	if (!OBBAxisOverlap(aYbY, a, b)) return false;

	Vect aZbY = aZ.cross(bY);
	if (!OBBAxisOverlap(aZbY, a, b)) return false;

	Vect aXbZ = aX.cross(bZ);
	if (!OBBAxisOverlap(aXbZ, a, b)) return false;

	Vect aYbZ = aY.cross(bZ);
	if (!OBBAxisOverlap(aYbZ, a, b)) return false;

	Vect aZbZ = aZ.cross(bZ);
	if (!OBBAxisOverlap(aZbZ, a, b)) return false;

	// all axes overlap
	return true;
}


