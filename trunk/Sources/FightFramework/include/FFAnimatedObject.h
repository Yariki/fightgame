#ifndef __FFANIMATEDOBJECT_H__
#define __FFANIMATEDOBJECT_H__

#include "FFInclude.h"


class FFAnimatedObject
{
protected:
	FF_ANIMATION_OBJECT	_currentAnimation;

public:
	FFAnimatedObject(void);
	virtual ~FFAnimatedObject(void);

public:
	virtual FF_ANIMATION_OBJECT	GetAnimation() = 0;
	virtual void				SetAnimation(FF_ANIMATION_OBJECT animation) = 0;

};

#endif //__FFANIMATEDOBJECT_H__