#ifndef __FFMOVABLEOBJECT_H__
#define __FFMOVABLEOBJECT_H__

#include "FFObject.h"
#include "FFDefines.h"
#include "FFEnums.h"

class FFMovableObject:public FFObject
{
protected:
	FF_MOVE_DIRECTION	_currentMoveDirection;
	FF_MOVE_OPERATION	_currentMoveOperation;
	//FFVector3			_speed;
	

public:
	FFMovableObject(void);
	FFMovableObject(orxSTRING filename);
	virtual ~FFMovableObject(void);

public:
	virtual void		Create();
	FF_MOVE_OPERATION	GetMoveOperation();
	void				SetMoveOperation(FF_MOVE_OPERATION moveOperation);
	FF_MOVE_DIRECTION	GetDirection();
	void				SetDirection(FF_MOVE_DIRECTION direction);
	virtual orxSTATUS	Update(const orxCLOCK_INFO* pClockInfo);

};

#endif //__FFMOVABLEOBJECT_H__