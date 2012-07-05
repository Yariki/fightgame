#ifndef __FFMOVABLEANIMATEDOBJECT_H__
#define __FFMOVABLEANIMATEDOBJECT_H__

#include "FFMovableObject.h"

class FFMovableAnimatedObject:public FFMovableObject
{
protected:
	orxSTRING _currentAnimationName;

public:
	FFMovableAnimatedObject(void);
	FFMovableAnimatedObject(orxSTRING filename);
	virtual ~FFMovableAnimatedObject(void);

	// ovveride method
public:
	void					Create();
	orxSTATUS				Update(const orxCLOCK_INFO* pClockInfo);

public:
	orxSTRING				GetAnimation();
	void					SetAnimation(orxSTRING animation);

};

#endif //__FFMOVABLEANIMATEDOBJECT_H__