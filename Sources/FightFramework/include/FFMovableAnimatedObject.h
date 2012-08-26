#ifndef __FFMOVABLEANIMATEDOBJECT_H__
#define __FFMOVABLEANIMATEDOBJECT_H__

#include "FFMovableObject.h"
#include "FFBaseController.h"

class FFMovableAnimatedObject:public FFMovableObject
{
protected:
	orxSTRING _currentAnimationName;
	FFBaseController* _controller;
	bool _isChanged;
public:
	FFMovableAnimatedObject(void);
	FFMovableAnimatedObject(orxSTRING filename);
	virtual ~FFMovableAnimatedObject(void);

	// ovveride method
public:
	void					Create();
	orxSTATUS				Update(const orxCLOCK_INFO* pClockInfo);
	void					UpdatePhysics(float deltaTime);
public:
	orxSTRING				GetAnimation();
	void					SetAnimation(orxSTRING animation);
	void					SetController(FFBaseController* controller);

};

#endif //__FFMOVABLEANIMATEDOBJECT_H__