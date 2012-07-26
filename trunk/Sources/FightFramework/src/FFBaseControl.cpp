
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

bool FFBaseControl::GetSmoothing()
{
	
	orxDISPLAY_SMOOTHING smooth = _mainObject != NULL ? orxObject_GetSmoothing(_mainObject) : orxDISPLAY_SMOOTHING_OFF;
	switch (smooth)
	{
	case orxDISPLAY_SMOOTHING_OFF:
		return false;
	case orxDISPLAY_SMOOTHING_ON:
		return true;
	}
	return false;
}

void FFBaseControl::SetSmoothing(bool isSmoothing)
{
	orxDISPLAY_SMOOTHING smooth;
	if(isSmoothing)
		smooth = orxDISPLAY_SMOOTHING_ON;
	else 
		smooth = orxDISPLAY_SMOOTHING_OFF;
	if(_mainObject)
		orxObject_SetSmoothing(_mainObject,smooth);
}

FF_COLOR FFBaseControl::GetColor()
{
	orxCOLOR clr;
	FF_COLOR res = {0};
	if(_mainObject)
	{
		orxObject_GetColor(_mainObject,&clr);
		res.R = clr.vRGB.fR;
		res.B = clr.vRGB.fB;
		res.G = clr.vRGB.fG;
	}
	return res;
}

void FFBaseControl::SetColor(FF_COLOR& color)
{
	orxCOLOR clr;
	clr.vRGB.fR = color.R;
	clr.vRGB.fB = color.B;
	clr.vRGB.fG = color.G;
	clr.fAlpha = color.A;
	if(_mainObject)
		orxObject_SetColor(_mainObject,(const orxCOLOR*)&clr);
}
