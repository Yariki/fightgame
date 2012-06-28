
#include "FFBaseControl.h"


FFBaseControl::FFBaseControl(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name)
{
	_parentForm = parent;
	_position = position;
	orxString_Copy(_caption,name);
}

FFBaseControl::~FFBaseControl()
{
	if(_mainObject)
		orxObject_Delete(_mainObject);
	if(_captionObject)
		orxObject_Delete(_captionObject);
}

void FFBaseControl::SetPause()
{
	_isPaused = true;
	if(_captionObject)
		orxObject_Pause(_captionObject,_isPaused);
	if(_mainObject)
		orxObject_Pause(_mainObject,_isPaused);
}

void FFBaseControl::Unpause()
{
	_isPaused = false;
	if(_captionObject)
		orxObject_Pause(_captionObject,_isPaused);
	if(_mainObject)
		orxObject_Pause(_mainObject,_isPaused);
}