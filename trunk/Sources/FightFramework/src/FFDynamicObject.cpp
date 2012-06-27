#include "FFDynamicObject.h"
#include "FFDynamicMoveStrategyFactory.h"


FFDynamicObject::FFDynamicObject(void)
{
	_type = FFDOT_DYNAMIC;
}

FFDynamicObject::FFDynamicObject(orxSTRING filename)
	:FFObject(filename)
{
	_type = FFDOT_DYNAMIC;
}


FFDynamicObject::~FFDynamicObject(void)
{
	if(_moveStrategy)
		delete _moveStrategy;
}

void FFDynamicObject::Create()
{
	if(std::string(_nameCfgFile).length() > 0)
	{
		orxConfig_Load(_nameCfgFile);
		orxSTRING section;
		switch(_type)
		{
		case FFSOT_STATIC:
			_object = orxObject_CreateFromConfig(FF_DYNAMIC_OBCJECT_SECTION_NAME);
			section = FF_DYNAMIC_OBCJECT_SECTION_NAME;
			break;
		case FFSOT_ANIMATED:
			_object = orxObject_CreateFromConfig(FF_DYNAMIC_ANIMATED_OBCJECT_SECTION_NAME);
			section = FF_DYNAMIC_ANIMATED_OBCJECT_SECTION_NAME;
			break;
		}

		orxSTATUS status = orxConfig_PushSection(section);
		if(status ==  orxSTATUS_SUCCESS)
		{
			const orxCHAR* strategy = orxConfig_GetString(MOVE_OBJECT_STRATEGY_PROPERTY);
			if(orxString_Compare(strategy,MOVE_OBJECT_STRATEGY_LINE) == 0)
			{
				// create strategy
				_moveStrategy = FFDynamicMoveStrategyFactory::CreateMoveStrategy(DS_LINE);
				_moveStrategy->ReadConfiguration();
			}
		}

		orxObject_SetUserData(_object,this);
	}
}

orxBOOL FFDynamicObject::IsMove()
{
	return _isMove;
}


void FFDynamicObject::Move()
{
	_isMove = true;
	if(_object)
		orxObject_Pause(_object,!_isMove);

}

void FFDynamicObject::Pause()
{
	_isMove = false;
	if(_object)
		orxObject_Pause(_object,!_isMove);
}

void FFDynamicObject::Stop()
{
	_isMove = false;
	if(_object)
		orxObject_Pause(_object,!_isMove);
}

void FFDynamicObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	if(_moveStrategy)
	{
		orxVECTOR pos ;
		orxObject_GetPosition(_object,&pos);
		_moveStrategy->Calculate(&pos,pClockInfo);
		orxObject_SetPosition(_object,&pos);
	}
}
