#include "BaseObject.h"


BaseObject::BaseObject(void)
{
	_object = NULL;
	_acceleration.fX = _acceleration.fY = _acceleration.fZ =  0.0f; 	
}


BaseObject::~BaseObject(void)
{
	if(_object)
		orxObject_Delete(_object);
}

void BaseObject::Create()
{
	orxSTATUS status;

	switch(_typeEntity)
	{
	case TE_STATIC:
		_object = orxObject_CreateFromConfig(WALL_SECTION);
		status = orxConfig_PushSection(WALL_SECTION);
		break;
	case TE_DYNAMIC:
		_object = orxObject_CreateFromConfig(OBJECT_SECTION);
		status = orxConfig_PushSection(OBJECT_SECTION);
		break;
	}
	if(status == orxSTATUS_SUCCESS && _object)
	{
		if(_typeEntity == TE_DYNAMIC)
		{
			orxConfig_GetVector(SPEED_SECTION,&_speed);
			_mass = orxConfig_GetFloat(MASS_SECTION);
			orxConfig_GetVector(FORCES_SECTION,&_forces);
		}
		orxConfig_GetVector(POSITION_SECTION,&_position);
		orxObject_SetPosition(_object,&_position);

		orxObject_GetPivot(_object,&_pivot);
		UpdateAABox();
	}
}

void BaseObject::UpdateAABox()
{
	if(_object)
	{
		orxObject_GetSize(_object,&_size);
		_aabox.vTL = _position;
		orxVector_Add(&_aabox.vBR,&_position,&_size);
	}
}