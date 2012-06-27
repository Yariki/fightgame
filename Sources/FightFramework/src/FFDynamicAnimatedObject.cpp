#include "FFDynamicAnimatedObject.h"

#define FF_D_AMINATION_LEFT					"LeftAnim"
#define FF_D_ANIMATION_RIGHT				"RightAnim"
#define FF_D_ANIMATION_DOWN					"DownAnim"
#define FF_D_ANIMATION_UP					"UpAnim"


FFDynamicAnimatedObject::FFDynamicAnimatedObject(void)
{
	_type = FFDOT_ANIMATED;
	_currentAnim = FFAD_LEFT;
}

FFDynamicAnimatedObject::FFDynamicAnimatedObject(orxSTRING filename)
	:FFDynamicObject(filename)
{
	_type = FFDOT_ANIMATED;
	_currentAnim = FFAD_LEFT;
}


FFDynamicAnimatedObject::~FFDynamicAnimatedObject(void)
{
}

FF_ANIMATION_DYNAMIC_OBJECT FFDynamicAnimatedObject::GetAnimation()
{
	return _currentAnim;
}


void FFDynamicAnimatedObject::SetAnimation(FF_ANIMATION_DYNAMIC_OBJECT animation)
{
	_currentAnim = animation;
	switch(_currentAnim)
	{
	case FFAD_LEFT:
		orxObject_SetTargetAnim(_object,FF_D_AMINATION_LEFT);
		break;
	case FFAD_RIGHT:
		orxObject_SetTargetAnim(_object,FF_D_ANIMATION_RIGHT);
		break;
	case FFAD_DOWN:
		orxObject_SetTargetAnim(_object,FF_D_ANIMATION_DOWN);
		break;
	case FFAD_UP:
		orxObject_SetTargetAnim(_object,FF_D_ANIMATION_UP);
		break;
	}
}

void FFDynamicAnimatedObject::Update(const orxCLOCK_INFO* pClockInfo)
{
	if(_moveStrategy)
	{
		orxVECTOR pos ;
		orxObject_GetPosition(_object,&pos);
		FF_ANIMATION_DYNAMIC_OBJECT anim = _moveStrategy->Calculate(&pos,pClockInfo);
		SetAnimation(anim);
		orxObject_SetPosition(_object,&pos);
	}
}