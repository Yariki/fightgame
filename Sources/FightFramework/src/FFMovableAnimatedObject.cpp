#include "FFMovableAnimatedObject.h"
#include "FFInputManager.h"


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
		_object = orxObject_CreateFromConfig(FF_MOVABLE_ANIMATED_OBJECT_SECTION_NAME);
		if(orxConfig_PushSection(FF_MOVABLE_ANIMATED_OBJECT_SECTION_NAME) == orxSTATUS_SUCCESS)
		{
			orxConfig_GetVector(FF_POSITION,&_position);
			orxConfig_GetVector(FF_SPEED,&_speed);

			orxConfig_PopSection();
		}

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
	orxSTATUS status =  orxObject_SetTargetAnim(_object,_currentAnimationName);
}

orxSTATUS FFMovableAnimatedObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR speed;
	orxVector_Mulf(&speed,&_speed,pClockInfo->fDT);

	bool isNew = false;


	orxObject_GetPosition(_object,&_position);
	if(FFInputManager::GetSingleton()->GetInputStatus(KEY_RIGHT,isNew))
	{
		
		_position.fX += speed.fX;
		_currentMoveDirection = FFMD_RIGHT;
		SetAnimation(FF_M_RIGHT_WALKING);
		SetPosition(_position);
	}
	else if(FFInputManager::GetSingleton()->GetInputStatus(KEY_LEFT,isNew))
	{
		
		_position.fX -= speed.fX;
		_currentMoveDirection =  FFMD_LEFT;
		SetAnimation(FF_M_LEFT_WALKING);
		SetPosition(_position);
	}
	else if(FFInputManager::GetSingleton()->GetInputStatus(KEY_UP,isNew))
	{
		orxVECTOR impulse;
		impulse.fX = 0.0;
		impulse.fY = -5.0;
		impulse.fZ = 0.0;
		orxObject_ApplyForce(_object,&impulse,NULL);
	}
	else
	{
		switch(_currentMoveDirection)
		{
		case FFMD_RIGHT:
			SetAnimation(FF_M_RIGHT_STAND);
			break;
		case FFMD_LEFT:
			SetAnimation(FF_M_LEFT_STAND);
			break;
		}
	}

	return orxSTATUS_SUCCESS;
}
