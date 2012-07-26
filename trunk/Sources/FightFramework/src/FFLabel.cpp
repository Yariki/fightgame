
#include "FFLabel.h"


FFLabel::FFLabel(FFBaseUiScene* parent, orxVECTOR& position, orxCHAR* name)
	:FFBaseControl(parent,position,name)
{
	_mainObject = orxObject_CreateFromConfig(LABEL_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject,&_position);
		orxObject_SetTextString(_mainObject,_caption);
	}
}

FFLabel::~FFLabel()
{

}


void FFLabel::SetCaption(std::string& caption)
{
	if(caption.length() == 0)
		return;

	orxCHAR* cap = (orxCHAR*)caption.c_str();
	orxString_Copy(_caption,cap);
	orxObject_SetTextString(_mainObject,_caption);
}