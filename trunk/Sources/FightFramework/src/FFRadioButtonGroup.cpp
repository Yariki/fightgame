#include "FFRadioButtonGroup.h"

#define DELTA_RADIO_BOX 20.0f


FFRadioButtonGroup::FFRadioButtonGroup(FFBaseUiScene* parent,FFVector3& position, orxCHAR* name)
	: FFBaseControl(parent,position,name)
{
    _posNextBox = _position;
    _currentIndex = _lastIndex = -1;
}

FFRadioButtonGroup::~FFRadioButtonGroup()
{
    for(size_t i = 0 ; i < _listButtons.size(); i++)
    {
        if(_listButtons.at(i)._item)
        {
            delete _listButtons.at(i)._item;
            _listButtons.at(i)._item = NULL;
        }
    }
    _listButtons.clear();
}

void FFRadioButtonGroup::Hide()
{
    for(size_t i = 0 ; i < _listButtons.size(); i++)
    {
        if(_listButtons.at(i)._item)
            _listButtons.at(i)._item->Hide();
    }
}

void FFRadioButtonGroup::Show()
{
    for(size_t i = 0 ; i < _listButtons.size(); i++)
    {
        if(_listButtons.at(i)._item)
            _listButtons.at(i)._item->Show();
    }
}

void FFRadioButtonGroup::AddItem(std::string& itemName)
{
    FFRadioItemData data;
    data._isChecked = false;
    int index = _listButtons.size();
    orxCHAR* name = (orxCHAR*)itemName.c_str();
    data._item = new FFRadioButton(_parentForm,this,
        _posNextBox,name,(RADIOCHOOSE)&FFRadioButtonGroup::OnChooseItem,index);
    _listButtons.push_back(data);
    _posNextBox._y += DELTA_RADIO_BOX;
}

void FFRadioButtonGroup::Update(orxOBJECT* obj)
{
    for(size_t i = 0; i < _listButtons.size(); i++)
    {
        if(_listButtons.at(i)._item)
            _listButtons.at(i)._item->Update(obj);
    }
    if(_currentIndex != _lastIndex)
    {
        for(size_t i = 0; i < _listButtons.size(); i++)
        {
            FFRadioButton* btn = _listButtons.at(i)._item;
            if(btn && _currentIndex == i && btn->GetState() == CHB_CHECK)
                btn->Check();
            else if(btn)
            {
                btn->SetState(CHB_NORMAL);
                btn->Normal();
            }
        }   
    }
    else
    {
        for(size_t i = 0; i < _listButtons.size(); i++)
        {
            FFRadioButton* btn = _listButtons.at(i)._item;
            if(btn)
                switch(btn->GetState())
                {
                case CHB_NORMAL:
                    btn->Normal(); 
                    break;
                case CHB_CHECK:
                    btn->Check();
                    break;
                };
        }        
    }
    _lastIndex = _currentIndex;
}

void FFRadioButtonGroup::OnChooseItem(int index)
{
    _currentIndex = index;
}

