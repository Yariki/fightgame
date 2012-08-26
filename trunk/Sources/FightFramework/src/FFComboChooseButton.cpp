#include "FFComboChooseButton.h"

FFComboChooseButton::FFComboChooseButton(FFBaseUiScene* parent, FFVector3& position, orxCHAR* name, COMBOCHANGE oncombochange)
	:FFBaseControl(parent,position,name)
{
	_OnChooseChange = oncombochange != NULL ? oncombochange : NULL;
	_currentItem = -1;
	_mainObject = orxObject_CreateFromConfig(CHOOSEBUTTON_SECTION);
	if(_mainObject)
	{
		orxObject_SetPosition(_mainObject, _position);
		for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		{
			const orxSTRING name = orxObject_GetName(obj);
			if(!orxString_Compare(name,BUTTON_LEFT_NAME))
			{
				_leftButton = obj;
			}
			else if(!orxString_Compare(name,BUTTON_RIGHT_NAME))
			{
				_rightButton = obj;
			}
			else if(!orxString_Compare(name,TEXT_CHOOSE))
			{
				_captionObject = obj;
			}
		}
	}
}

FFComboChooseButton::~FFComboChooseButton()
{
	_leftButton = orxNULL;
	_rightButton = orxNULL;
	_OnChooseChange = NULL;
}

void FFComboChooseButton::Update(orxOBJECT* obj)
{
	bool isNew = false;
	bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);
	if(obj == _leftButton)
		if( isLeft && isNew)
		{
			PressLeft();
			SetCurrentItem(true);
			if(_OnChooseChange)
				(_parentForm->*_OnChooseChange)(_items.at(_currentItem));
		}
		else if(isLeft && !isNew)
		{
			PressLeft();
		}
		else
		{
			HoverLeft();
		}
	else if(obj == _rightButton)
		if(isLeft && isNew)
		{
			PressRight();
			SetCurrentItem(false);
			if(_OnChooseChange)
				(_parentForm->*_OnChooseChange)(_items.at(_currentItem));

		}
		else if(isLeft && !isNew)
		{
			PressRight();
		}
		else
			HoverRight();
	else
	{
		NormalLeft();
		NormalRight();
	}

}

void FFComboChooseButton::AddItem(string item)
{
	_items.push_back(item);
	if(_items.size() == 1)
	{
		SetCurrentItem(false);
	}
}

void FFComboChooseButton::SetCurrentItem(bool direction)
{
	if(direction)
	{
		_currentItem--;
		if(_currentItem < 0)
			_currentItem = _items.size() - 1;
	}
	else
	{
		_currentItem++;
		if(_currentItem >= (int)_items.size())
			_currentItem = 0;
	}
	orxObject_SetTextString(_captionObject,_items.at(_currentItem).c_str());
}