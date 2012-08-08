#include "DynamicObject.h"


DynamicObject::DynamicObject(void)
{
	_typeEntity =  TE_DYNAMIC;

}


DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::Update(float deltaTime)
{
	orxVECTOR temp;
	orxVector_Mulf(&temp,&_speed,deltaTime);
	orxVector_Add(&_position,&_position,&temp);
	if(_object)
		orxObject_SetPosition(_object,&_position);
	float g = _mass * deltaTime;
	//_speed.fX += g;
	_speed.fY += g;
	UpdateAABox();
}