#include "FFButton.h"


FFButton::FFButton(FFBaseUiScene* parent,FFVector3& position, orxCHAR* name, BUTTONCLICK onckick)
	:FFBaseControl(parent,position,name)
{
	_OnClick = onckick != NULL ? onckick : NULL;
	_mainObject = orxObject_CreateFromConfig(BUTTON_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject,_position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,BUTTON_CAPTION_NAME))
			{
				_captionObject = obj;
				orxObject_SetTextString(_captionObject,_caption);
                CalcCaptionPosition();
			}
		}
	}
	_clickPress = false;
}

FFButton::~FFButton()
{
	_OnClick = NULL;
}

void FFButton::Update(orxOBJECT* obj)
{
	bool isNew = false;
	bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);

	if(!obj)
	{
		Normal();
		return;
	}

	if(obj == _mainObject || obj == _captionObject)
	{
		if(isLeft && isNew)
		{
			Press();
			_clickPress = true;
		}
		else if(isLeft && !isNew)
		{
			Press();
			if(_clickPress && _OnClick)
			{
				 (_parentForm->*_OnClick)();
				 _clickPress = false;
			}
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
	{
		orxObject_SetTargetAnim(_mainObject,BUTTON_ANIMATION_HOVER);
		
	}
}

void FFButton::Normal()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,BUTTON_ANIMATION_NORMAL);
}

void FFButton::CalcCaptionPosition()
{
    const orxFONT* def = orxFont_GetDefaultFont();
    orxU32 lenght = orxString_GetLength(_caption);
    float stringWidth = 0.0f;
    for(orxU32 i = 0; i < lenght; i++)
        stringWidth += orxFont_GetCharacterWidth(def,_caption[i]);
    FFVector3 sizeMain;
	orxVECTOR t;
    orxObject_GetSize(_mainObject,&t);
	sizeMain = t;
    FFVector3 posCaption;
    posCaption._x = 0.0f;
    posCaption._y = 3.0f;
    posCaption._z = 0.0f;
    float delta = sizeMain._x - stringWidth;
    if(delta > 0)
    {
        delta /=2.0f;
        posCaption._x = delta;
        orxObject_SetPosition(_captionObject,posCaption);
    }
    else
        orxObject_SetPosition(_captionObject,posCaption);
}