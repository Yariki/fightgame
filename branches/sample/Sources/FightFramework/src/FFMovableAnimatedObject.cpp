#include "FFMovableAnimatedObject.h"

#define SPEED			"Speed"

FFMovableAnimatedObject::FFMovableAnimatedObject(void)
{
}

FFMovableAnimatedObject::FFMovableAnimatedObject(orxSTRING filename)
	:FFMovableObject(filename)
{
}


FFMovableAnimatedObject::~FFMovableAnimatedObject(void)
{
}

void FFMovableAnimatedObject::Create()
{
	if(std::string(_nameCfgFile).length() > 0)
	{
		orxConfig_Load(_nameCfgFile);
		_object = orxObject_CreateFromConfig(FF_MOVABLE_ANIMATED_OBCJECT_SECTION_NAME);
		orxConfig_GetVector(SPEED,&_speed);

		orxConfig_Clear();
		orxObject_SetUserData(_object,this);
	}
}

orxSTRING FFMovableAnimatedObject::GetAnimation()
{
	return _currentAnimationName;
}

void FFMovableAnimatedObject::SetAnimation(orxSTRING animation)
{
	_currentAnimationName = animation;
	orxObject_SetTargetAnim(_object,_currentAnimationName);
}

orxSTATUS FFMovableAnimatedObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR speed;
	orxVector_Mulf(&speed,&_speed,pClockInfo->fDT);

	if(orxInput_IsActive(FF_M_RIGHT_WALKING))
	{
		_position.fX += speed.fX;
		_currentMoveDirection = FFMD_RIGHT;
		SetAnimation(FF_M_RIGHT_WALKING);
	}
	else if(orxInput_IsActive(FF_M_LEFT_WALKING))
	{
		_position.fX -= speed.fX;
		_currentMoveDirection =  FFMD_LEFT;
		SetAnimation(FF_M_LEFT_WALKING);
	}

	SetPosition(_position);

	return orxSTATUS_SUCCESS;
}
