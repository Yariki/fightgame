#ifndef __FFOBJECT_H__
#define __FFOBJECT_H__

#include "FFInclude.h"

class FFObject
{
protected:
	orxVECTOR*	_size;
	orxCOLOR	_color;
	orxCHAR	_nameCfgFile[MAX_FILE_PATH];
	orxVECTOR	_position;
	orxFLOAT	_rotation;
	orxVECTOR	_scale;

	orxOBJECT*	_object;

public:
	FFObject(void);
	FFObject(orxSTRING filename);
	virtual ~FFObject(void);

public:
	virtual void		Create() = 0;
	orxCOLOR			GetColor();
	orxVECTOR			GetPosition();
	orxFLOAT			GetRotation();
	orxVECTOR			GetScale();
	orxVECTOR*			GetSize();
	
	void				SetColor(orxCOLOR& color);
	void				SetPosition(orxVECTOR& pos);
	void				SetRotation(orxFLOAT& rot);
	void				SetScale(orxVECTOR& scale);

};

#endif //__FFOBJECT_H__