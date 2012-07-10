#include "FFRadioButton.h"


FFRadioButton::FFRadioButton(FFBaseUiScene* parent,FFRadioButtonGroup* group, orxVECTOR& pos, orxCHAR* name,RADIOCHOOSE onchoose,int index = -1)
    :FFBaseControl(parent,pos,name)
{
    _OnChoose = onchoose != NULL ? onchoose : NULL;
    _state = CHB_NORMAL;
    _group = group;
    _mainObject = orxObject_CreateFromConfig(RADIO_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject,&_position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,RADIO_CAPTION_SECTION))
			{
				_captionObject = obj;
				orxObject_SetTextString(_captionObject,_caption);
			}
		}
	}
}

FFRadioButton::~FFRadioButton()
{
    _OnChoose = NULL;
}

void FFRadioButton::Update(orxOBJECT* obj)
{
    bool isNew = false;
	bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);
	if(obj == _mainObject || obj == _captionObject)
	{
		if(isLeft && isNew)
		{
			SetState(CHB_CHECK);
            if(_OnChoose && _group)
            {
                
            }
		}
	}
}

void FFRadioButton::SetState(FF_UI_CHECKBOX_STATE state)
{
    _state = state;
}

void FFRadioButton::Normal()
{
    if(_mainObject)
        orxObject_SetTargetAnim(_mainObject,RADIO_ANIMATION_NORMAL);
}

void FFRadioButton::Check()
{
    if(_mainObject)
        orxObject_SetTargetAnim(_mainObject,RADIO_ANIMATION_CHECK);
}
