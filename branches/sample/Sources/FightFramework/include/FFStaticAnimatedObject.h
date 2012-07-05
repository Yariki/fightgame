#ifndef __FFSTATICANIMATEDOBJECT_H__
#define __FFSTATICANIMATEDOBJECT_H__

#include "FFAnimatedObject.h"
#include "FFStaticObject.h"


class FFStaticAnimatedObject:public FFStaticObject,public FFAnimatedObject
{
protected:
	FF_ANIMATION_OBJECT		_currentAnim;
	//orxCLOCK*				_pClockAnim;


public:
	FFStaticAnimatedObject(void);
	FFStaticAnimatedObject(orxSTRING filename);
	virtual ~FFStaticAnimatedObject(void);



public:
	void					Create();
	FF_ANIMATION_OBJECT		GetAnimation();
	void					SetAnimation(FF_ANIMATION_OBJECT animation);
	void					UpdateAnimation(const orxCLOCK_INFO* pClockInfo);

	virtual void Update(const orxCLOCK_INFO* pClockInfo);


	
};

#endif //__FFSTATICANIMATEDOBJECT_H__