#include "FFMovableAnimatedObject.h"
#include "FFInputManager.h"


FFMovableAnimatedObject::FFMovableAnimatedObject(void)
{
	_controller =  NULL;
}

FFMovableAnimatedObject::FFMovableAnimatedObject(orxSTRING filename)
	:FFMovableObject(filename)
{
	_controller =  NULL;
	_isChanged = false;
}


FFMovableAnimatedObject::~FFMovableAnimatedObject(void)
{
	_controller = NULL;
}

void FFMovableAnimatedObject::Create()
{
	if(std::string(_nameCfgFile).length() > 0)
	{
		orxConfig_Load(_nameCfgFile);
		_object = orxObject_CreateFromConfig(FF_MOVABLE_ANIMATED_OBJECT_SECTION_NAME);
		if(orxConfig_PushSection(FF_MOVABLE_ANIMATED_OBJECT_SECTION_NAME) == orxSTATUS_SUCCESS)
		{

			orxCHAR temp[MAX_FILE_PATH];
			orxString_Copy(temp,orxConfig_GetString(ENTITY_TYPE_SECTION));
			if(!orxString_Compare(temp,ENTITY_TYPE_DYNAMIC_VALUE))
				_typeEntity = FTE_DYNAMIC;

			orxVECTOR a;
			orxConfig_GetVector(FF_POSITION,&a);
			_position = a;
			//orxObject_SetPosition(_object,(orxVECTOR*)_position);
			orxConfig_GetVector(FF_SPEED,&a);
			_speed = a;
			orxConfig_GetVector(FORCES_SECTION,&a);
			_forces = a;
			_mass = orxConfig_GetFloat(MASS_SECTION);

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
	
	orxVECTOR temp;
	bool isNew = false;
	_isChanged = false;
	if(_controller)
	{
		if(_controller->IsUp(isNew) && isNew)
		{
			FFVector3 speed(0.0,-300,0.0);
			SetSpeed(speed);
			_isChanged = true;
		}
		if(_controller->IsRight(isNew))
		{

			FFVector3 speed(150.0,0,0.0);
			SetSpeed(speed);
			_currentMoveDirection = FFMD_RIGHT;
			SetAnimation(FF_M_RIGHT_WALKING);
			_isChanged = true;
		}
		else if(_controller->IsLeft(isNew))
		{
			FFVector3 speed(-150.0,0,0.0);
			SetSpeed(speed);
			_currentMoveDirection =  FFMD_LEFT;
			SetAnimation(FF_M_LEFT_WALKING);
			_isChanged = true;
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
	}

	return orxSTATUS_SUCCESS;
}

void FFMovableAnimatedObject::SetController(FFBaseController* controller)
{
	_controller = controller;
}

void FFMovableAnimatedObject::UpdatePhysics(float deltaTime)
{
	FFVector3 temp;
	temp = _speed * deltaTime;
	_position += temp;
	if(_object)
		orxObject_SetPosition(_object,(orxVECTOR*)_position);
	float g = _mass * deltaTime;
	//_speed._x += g;
	_speed._y += g;
	UpdateAABox();
}
