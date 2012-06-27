#ifndef __FFBASECONTROL_H__
#define __FFBASECONTROL_H__

#include "FFInclude.h"

#define MAX_NAME 260


class FFBaseControl
{
protected:
	orxOBJECT*	_mainObject;
	orxOBJECT* _captionObject;
	orxVECTOR _position;
	orxCHAR _caption[MAX_NAME];

public:
	FFBaseControl(orxVECTOR& position, orxCHAR* name);
	virtual ~FFBaseControl();

public:
	void SetPause(bool pause);
	void Unpause();
	virtual void Update(orxOBJECT* obj) = 0;
};


#endif //__FFBASECONTROL_H__