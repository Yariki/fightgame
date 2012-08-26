#include "FFObject.h"


FFObject::FFObject(void)
{
	_object = NULL;
	_hitSide = FHS_NONE;
	_typeEntity = FTE_NONE;
}

FFObject::FFObject(orxSTRING filename)
{
	orxString_Copy(_nameCfgFile,filename);
	_object = orxObject_CreateFromConfig(_nameCfgFile);
	_hitSide = FHS_NONE;
	_typeEntity = FTE_NONE;
}


FFObject::~FFObject(void)
{
	if(_object)
		orxObject_Delete(_object);
}

orxCOLOR FFObject::GetColor()
{
	return _color;
}

FFVector3 FFObject::GetPosition()
{
	return _position;
}

orxFLOAT FFObject::GetRotation()
{
	return _rotation;
}

FFVector3 FFObject::GetScale()
{
	return _scale;
}

FFVector3 FFObject::GetSize()
{
	if(_object)
	{
		orxVECTOR a;
		orxObject_GetSize(_object,&a);
		_size = a;
		return _size;
	}
	else
	{
		return FFVector3(0.0,0.0,0.0);
	}
}

void FFObject::SetColor(orxCOLOR& color)
{
	_color = color;
	if(_object)
		orxObject_SetColor(_object,&_color);
}

void FFObject::SetPosition(FFVector3& pos)
{
	if(&_position != &pos)
		_position = pos;
	if(_object)
		orxObject_SetPosition(_object,_position);
	UpdateAABox();
}

void FFObject::SetRotation(orxFLOAT& rot)
{
	_rotation = rot;
	if(_object)
		orxObject_SetRotation(_object, _rotation);
}

void FFObject::SetScale(FFVector3& scale)
{
	_scale = scale;
	if(_object)
		orxObject_SetScale(_object,_scale);
}

void FFObject::SetSpeed(FFVector3& speed)
{
	switch(_hitSide)
	{
	case FHS_NONE:
		_speed._x = speed._x;
		break;
	case FHS_LEFT:
		if(_speed._x > 0)
			_speed._x = speed._x;
		break;
	case FHS_RIGHT:
		if(speed._x < 0)
			_speed._x = speed._x;
		break;
	}
	if(_speed._y == 0)
		_speed._y = speed._y;
}

bool FFObject::IsMove()
{
	return _speed._x != 0 || _speed._y != 0;
}

void FFObject::Stop()
{
	_speed.Zero();
	_acceleration.Zero();
	_forces.Zero();
}

void FFObject::UpdateAABox()
{
	if(_object)
	{
		orxVECTOR temp;
		orxVECTOR scale;
		orxObject_GetSize(_object,&temp);
		_size = temp;
		_aabox.vTL = _position;
		_aabox.vBR = (_position + _size);
	}
}
