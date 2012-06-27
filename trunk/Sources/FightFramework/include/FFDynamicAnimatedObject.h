#ifndef __FFDYNAMICANIMATEDOBJECT_H__
#define __FFDYNAMICANIMATEDOBJECT_H__

#include "FFAnimatedObject.h"
#include "FFDynamicObject.h"

class FFDynamicAnimatedObject:public FFDynamicObject
{
protected:
	FF_ANIMATION_DYNAMIC_OBJECT		_currentAnim;
public:
	FFDynamicAnimatedObject(void);
	FFDynamicAnimatedObject(orxSTRING filename);
	virtual ~FFDynamicAnimatedObject(void);

public:
	FF_ANIMATION_DYNAMIC_OBJECT		GetAnimation();
	void							SetAnimation(FF_ANIMATION_DYNAMIC_OBJECT animation);
		
	void							Update(const orxCLOCK_INFO* pClockInfo);					

};

#endif //__FFDYNAMICANIMATEDOBJECT_H__