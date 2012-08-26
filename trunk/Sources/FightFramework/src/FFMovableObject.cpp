#include "FFMovableObject.h"
#include "FFInputManager.h"


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
		_object = orxObject_CreateFromConfig(FF_MOVABLE_OBJECT_SECTION_NAME);
		if(orxConfig_PushSection(FF_MOVABLE_OBJECT_SECTION_NAME) == orxSTATUS_SUCCESS)
		{
			orxVECTOR a;
			orxConfig_GetVector(FF_POSITION,&a);
			_position = a;
			orxConfig_GetVector(FF_SPEED,&a);
			_speed = a;

			orxConfig_PopSection();
		}


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

void FFMovableObject::SetMoveOperation(FF_MOVE_OPERATION moveOperation)
{
	_currentMoveOperation = moveOperation;
}

orxSTATUS FFMovableObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	//orxVECTOR speed;
	//orxVector_Mulf(&speed,&_speed,pClockInfo->fDT);
	bool isNew = false;
	if(FFInputManager::GetSingleton()->GetInputStatus(KEY_RIGHT,isNew))
	{
		//_position.fX += speed.fX;
		_currentMoveDirection = FFMD_RIGHT;
		
	}
	else if(FFInputManager::GetSingleton()->GetInputStatus(KEY_LEFT,isNew))
	{
		//_position.fX -= speed.fX;
		_currentMoveDirection =  FFMD_LEFT;
		
	}

	SetPosition(_position);

	return orxSTATUS_SUCCESS;
}