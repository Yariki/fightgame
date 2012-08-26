#ifndef __FFSTATICOBJECT_H_
#define __FFSTATICOBJECT_H_


#include "FFObject.h"


class FFStaticObject: public FFObject
{
protected:
	FF_STATIC_OBJECT_TYPE _type;
	FFVector3 _repeat;
public:
	FFStaticObject(void);
	FFStaticObject(orxSTRING filename);
	virtual ~FFStaticObject(void);

	virtual void Update(const orxCLOCK_INFO* pClockInfo) {}
	void		 UpdatePhysics(float deltaTime);

public:
	void Create();

protected:
	void UpdateAABox();

};

#endif //__FFSTATICOBJECT_H_