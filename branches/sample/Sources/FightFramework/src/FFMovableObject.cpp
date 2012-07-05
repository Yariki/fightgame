#include "FFMovableObject.h"

#define SPEED			"Speed"

FFMovableObject::FFMovableObject(void)
{
}

FFMovableObject::FFMovableObject(orxSTRING filename)
	:FFObject(filename)
{
	
}

FFMovableObject::~FFMovableObject(void)
{

}

void FFMovableObject::Create()
{
	if(std::string(_nameCfgFile).length() > 0)
	{
		orxConfig_Load(_nameCfgFile);
		_object = orxObject_CreateFromConfig(FF_MOVABLE_OBCJECT_SECTION_NAME);
		orxConfig_GetVector(SPEED,&_speed);

		orxConfig_Clear();
		orxObject_SetUserData(_object,this);
	}
}

FF_MOVE_DIRECTION FFMovableObject::GetDirection()
{
	return _currentMoveDirection;
}

void FFMovableObject::SetDirection(FF_MOVE_DIRECTION direction)
{
	_currentMoveDirection = direction;
}

FF_MOVE_OPERATION FFMovableObject::GetMoveOperation()
{
	return _currentMoveOperation;
}

void FFMovableObject::SetMoveOpertion(FF_MOVE_OPERATION moveOperation)
{
	_currentMoveOperation = moveOperation;
}

orxSTATUS FFMovableObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR speed;
	orxVector_Mulf(&speed,&_speed,pClockInfo->fDT);

	if(orxInput_IsActive(FF_M_RIGHT_WALKING))
	{
		_position.fX += speed.fX;
		_currentMoveDirection = FFMD_RIGHT;
	}
	else if(orxInput_IsActive(FF_M_LEFT_WALKING))
	{
		_position.fX -= speed.fX;
		_currentMoveDirection =  FFMD_LEFT;
	}

	SetPosition(_position);

	return orxSTATUS_SUCCESS;
}