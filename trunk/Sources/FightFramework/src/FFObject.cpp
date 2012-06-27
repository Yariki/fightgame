#include "FFObject.h"


FFObject::FFObject(void)
{
	_object = orxObject_Create();
}

FFObject::FFObject(orxSTRING filename)
{
	orxString_Copy(_nameCfgFile,filename);
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

orxVECTOR FFObject::GetPosition()
{
	return _position;
}

orxFLOAT FFObject::GetRotation()
{
	return _rotation;
}

orxVECTOR FFObject::GetScale()
{
	return _scale;
}

orxVECTOR* FFObject::GetSize()
{
	if(_object)
	{
		orxObject_GetSize(_object,_size);
		return _size;
	}
	else
	{
		return orxNULL;
	}
}

void FFObject::SetColor(orxCOLOR& color)
{
	_color = color;
	if(_object)
		orxObject_SetColor(_object,&_color);
}

void FFObject::SetPosition(orxVECTOR& pos)
{
	_position = pos;
	if(_object)
		orxObject_SetPosition(_object,&_position);
}

void FFObject::SetRotation(orxFLOAT& rot)
{
	_rotation = rot;
	if(_object)
		orxObject_SetRotation(_object, _rotation);
}

void FFObject::SetScale(orxVECTOR& scale)
{
	_scale = scale;
	if(_object)
		orxObject_SetScale(_object,&_scale);
}
