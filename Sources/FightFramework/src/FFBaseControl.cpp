
#include "FFBaseControl.h"


FFBaseControl::FFBaseControl(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name)
{
	_parentForm = parent;
	_position = position;
    _mainObject = orxNULL;
    _captionObject = orxNULL;
    if(name != orxNULL)
	    orxString_Copy(_caption,name);
}

FFBaseControl::~FFBaseControl()
{
	if(_mainObject)
		orxObject_Delete(_mainObject);
	if(_captionObject)
		orxObject_Delete(_captionObject);
}

void FFBaseControl::Show()
{
	_isHide = true;
	if(_captionObject)
		orxObject_Enable(_captionObject,_isHide);
	if(_mainObject)
		orxObject_Enable(_mainObject,_isHide);
}

void FFBaseControl::Hide()
{
	_isHide = false;
	if(_captionObject)
		orxObject_Enable(_captionObject,_isHide);
	if(_mainObject)
		orxObject_Enable(_mainObject,_isHide);
}

void FFBaseControl::SetScale(orxVECTOR* scale)
{
    if(_mainObject)
        orxObject_SetScale(_mainObject,scale);
}

void FFBaseControl::SetPosition(orxVECTOR* pos)
{
    _position.fX = pos->fX;
    _position.fY = pos->fY;
    _position.fZ = pos->fZ;
    if(_mainObject)
        orxObject_SetPosition(_mainObject,&_position);

}
