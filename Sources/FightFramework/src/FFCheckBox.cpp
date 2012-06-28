#include "FFCheckBox.h"


FFCheckBox::FFCheckBox(FFBaseUiScene* parent, orxVECTOR& position, orxCHAR* name, 
	CHECKCHANGE oncheckchange)
	:FFBaseControl(parent,position,name)
{
	_OnCheckChange = oncheckchange != NULL ? oncheckchange : NULL;
	_mainObject = orxObject_CreateFromConfig(CHECKBOX_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject,&_position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,CHECKBOX_CAPTION_SECTION))
			{
				_captionObject = obj;
				orxObject_SetTextString(_captionObject,_caption);
			}
		}
	}

}

FFCheckBox::~FFCheckBox()
{
	_OnCheckChange = NULL;
}

void FFCheckBox::Update(orxOBJECT* obj)
{
	bool isNew = false;
	bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);
	if(obj == _mainObject || obj == _captionObject)
	{
		if(isLeft && isNew && GetState() == CHB_NORMAL)
		{
			Check();
			SetState(CHB_CHECK);
			if(_OnCheckChange)
				(_parentForm->*_OnCheckChange)(true);
		}
		else if(isLeft && isNew && GetState() == CHB_CHECK)
		{
			Normal();
			SetState(CHB_NORMAL);
			if(_OnCheckChange)
				(_parentForm->*_OnCheckChange)(false);
		}
	}
	else
		Normal();
}

void FFCheckBox::Normal()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,CHECKBOX_ANIMATION_NORMAL);
}

void FFCheckBox::Check()
{
	if(_mainObject)
		orxObject_SetTargetAnim(_mainObject,CHECKBOX_ANIMATION_CHECK);

}

