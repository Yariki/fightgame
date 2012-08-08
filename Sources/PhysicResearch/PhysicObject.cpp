#include "PhysicObject.h"


PhysicObject::PhysicObject(void)
{
}


PhysicObject::~PhysicObject(void)
{
}

void PhysicObject::SetPosition(const orxVECTOR* position)
{
	orxVector_Copy(&_position,position);
	if(_object)
		orxObject_SetPosition(_object,&_position);
	UpdateAABox();
}

void PhysicObject::SetAcceleration(const orxVECTOR* acceleration)
{
	orxVector_Copy(&_acceleration,acceleration);
}

void PhysicObject::SetSpeed(const orxVECTOR* speed)
{
	switch(_hitSide)
	{
	case HS_NONE:
		_speed.fX = speed->fX;
		break;
	case HS_LEFT:
		if(speed->fX > 0)
			_speed.fX = speed->fX;
		break;
	case HS_RIGHT:
		if(speed->fX < 0)
			_speed.fX = speed->fX;
		break;
	}
	if(_speed.fY == 0)
		_speed.fY = speed->fY;
}

bool PhysicObject::IsMove()
{
	return _speed.fX != 0 || _speed.fY != 0;
}

void PhysicObject::Stop()
{
	_speed.fX = _speed.fY = _speed.fZ = 0.0;
	_acceleration.fY = _acceleration.fZ = 0.0;
	_forces.fY = _forces.fZ = 0.0;
}

