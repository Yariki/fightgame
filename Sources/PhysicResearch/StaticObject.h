#ifndef  __STATICOBJECT_H__
#define __STATICOBJECT_H__

#include "physicobject.h"


class StaticObject :
	public PhysicObject
{
public:
	StaticObject(void);
	virtual ~StaticObject(void);
};

#endif //__STATICOBJECT_H__