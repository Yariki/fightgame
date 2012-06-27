#ifndef __FFSTATICOBJECT_H_
#define __FFSTATICOBJECT_H_


#include "FFObject.h"


class FFStaticObject: public FFObject
{
protected:
	FF_STATIC_OBJECT_TYPE _type;

public:
	FFStaticObject(void);
	FFStaticObject(orxSTRING filename);
	virtual ~FFStaticObject(void);



public:
	void Create();

};

#endif //__FFSTATICOBJECT_H_