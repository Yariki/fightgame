#include "FFButton.h"


FFButton::FFButton(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name, BUTTONCLICK onckick)
	:FFBaseControl(parent,position,name)
{
	_OnClick = onckick != NULL ? onckick : NULL;
	_mainObject = orxObject_CreateFromConfig(BUTTON_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject,&_position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,BUTTON_CAPTION_NAME))
			{
				_captionObject = obj;
				orxObject_SetTextString(_captionObject,_caption);
			}
		}
	}
}

FFButton::~FFButton()
{
	_OnClick = NULL;
}

void FFButton::Update(orxOBJECT* obj)
{
	bool isNew = false;
	bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);
	if(obj == _mainObject || obj == _captionObject)
	{
		if(isLeft && isNew)
		{
			Press();
			if(_OnClick)
			 	(_parentForm->*_OnClick)();
		}
		else if(isLeft && !isNew)
		{
			Press();
		}
		else
			Hover();
	}
	else
		Normal();
}

void FFButton::Press()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,BUTTON_ANIMATION_PRESS);
}

void FFButton::Hover()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,BUTTON_ANIMATION_HOVER);
}

void FFButton::Normal()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,BUTTON_ANIMATION_NORMAL);
}