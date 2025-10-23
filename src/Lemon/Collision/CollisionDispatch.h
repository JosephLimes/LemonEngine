#ifndef _CollisionDispatch
#define _CollisionDispatch

#include "CollisionDispatchBase.h"

template < typename T1, typename T2 >
class CollisionDispatch : public CollisionDispatchBase
{
public:
	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch&) = delete;
	CollisionDispatch operator = (const CollisionDispatch&) = delete;
	virtual ~CollisionDispatch() = default;

	virtual void ProcessCallbacks(Collidable* pObj1, Collidable* pObj2) override
	{
		T1* pTypeObj1 = static_cast<T1*>(pObj1);
		T2* pTypeObj2 = static_cast<T2*>(pObj2);

		pTypeObj1->Collision(pTypeObj2);
		pTypeObj2->Collision(pTypeObj1);
	};
};

#endif _CollisionDispatch