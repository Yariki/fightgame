#ifndef __FFDYNAMICOBJECT_H__
#define __FFDYNAMICOBJECT_H__

#include "FFObject.h"
#include "IDynamicMoveStrategy.h"

//property
#define	MOVE_OBJECT_STRATEGY_PROPERTY		"Strategy"

//value
#define MOVE_OBJECT_STRATEGY_LINE			"line"

class FFDynamicObject:public FFObject
{
protected:
	orxBOOL					_isMove;
	FF_DYNAMIC_OBJECT_TYPE	_type;
	IDynamicMoveStrategy*	_moveStrategy;


public:
	FFDynamicObject(void);
	FFDynamicObject(orxSTRING filename);
	virtual ~FFDynamicObject(void);

public:
	void				Create();
	orxBOOL				IsMove();
	void				Move();
	void				Pause();
	void				Stop();
	virtual void		Update(const orxCLOCK_INFO* pClockInfo);
	

};

#endif //__FFDYNAMICOBJECT_H__