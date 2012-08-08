#ifndef __PHYSICOBJECT_H__
#define __PHYSICOBJECT_H__

#include "BaseObject.h"

class PhysicObject : public BaseObject
{
public:
	PhysicObject(void);
	virtual ~PhysicObject(void);


	const orxVECTOR* GetPosition() {return &_position ;}
	void SetPosition(const orxVECTOR* position);

	orxFLOAT GetMass() {return _mass;}
	const orxVECTOR* GetPivot(){return &_pivot;}
	const orxVECTOR* GetSize() {return &_size;}

	const orxVECTOR* GetAcceleration() {return  &_acceleration;}
	void SetAcceleration(const orxVECTOR* acceleration);

	const orxVECTOR* GetSpeed() {return &_speed;}
	void SetSpeed(const orxVECTOR* speed);

	bool IsMove();

	void Stop();

};

#endif //__PHYSICOBJECT_H__