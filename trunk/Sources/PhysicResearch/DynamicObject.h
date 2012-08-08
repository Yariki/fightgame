#ifndef __DYNAMICOBJECT_H__
#define __DYNAMICOBJECT_H__

#include "PhysicObject.h"

class DynamicObject : public PhysicObject
{
public:
	DynamicObject(void);
	virtual ~DynamicObject(void);

	virtual void Update(float deltaTime);

};

#endif //__DYNAMICOBJECT_H__
