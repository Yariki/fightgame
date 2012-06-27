#include "FFStaticAnimatedObject.h"


FFStaticAnimatedObject::FFStaticAnimatedObject(void)
{
	_type = FFSOT_ANIMATED;
	_currentAnim = FFAO_MAIN;
}

FFStaticAnimatedObject::FFStaticAnimatedObject(orxSTRING filename)
	:FFStaticObject(filename)
{
	_type = FFSOT_ANIMATED;
	_currentAnim = FFAO_MAIN;
}


FFStaticAnimatedObject::~FFStaticAnimatedObject(void)
{
}

void FFStaticAnimatedObject::Create()
{
	FFStaticObject::Create();
	orxCLOCK* pClockAnim = orxClock_FindFirst(orx2F(-1.0f),orxCLOCK_TYPE_CORE);
	if(pClockAnim)
	{
		orxClock_Register(pClockAnim,Update,this,orxMODULE_ID_MAIN,
			orxCLOCK_PRIORITY_NORMAL);
	}
}



FF_ANIMATION_OBJECT FFStaticAnimatedObject::GetAnimation()
{
	return _currentAnim;
}


void FFStaticAnimatedObject::SetAnimation(FF_ANIMATION_OBJECT animation)
{
	_currentAnim = animation;
	if(_object)
	{
		switch(animation)
		{
		case FFAO_MAIN:
			orxObject_SetTargetAnim(_object,FF_SD_ANIMATION_MAIN);
			break;
		case FFAO_HELPER1:
			break;
		}
		
	}
}

void FFStaticAnimatedObject::Update(const orxCLOCK_INFO* pClockInfo, void* pContext)
{
	FFStaticAnimatedObject* obj = static_cast<FFStaticAnimatedObject*>(pContext);
	if(obj)
	{
		obj->UpdateAnimation(pClockInfo);
	}
}

void FFStaticAnimatedObject::UpdateAnimation(const orxCLOCK_INFO* pClockInfo)
{
	SetAnimation(FFAO_MAIN);
}


