#include "FFPreview.h"


FFPreview::FFPreview(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name,const orxCHAR* filepreview,ITEMCHOOSE onitemchoose, int number = -1)
    :FFBaseControl(parent,position,name)
{
    _OnChoose = onitemchoose != NULL ? onitemchoose : NULL;
    
    _number = number;
    orxString_Copy(_filePreview ,filepreview);
    if(orxConfig_Load(_filePreview) == orxSTATUS_SUCCESS)
    {
        _mainObject = orxObject_CreateFromConfig(PREVIEW_SECTION);
        if(_mainObject)
        {
            orxObject_SetPosition(_mainObject,&_position);
            if(orxConfig_PushSection(PREVIEW_SECTION) == orxSTATUS_SUCCESS)
            {
                orxString_Copy(_caption,orxConfig_GetString(PREVIEW_CAPTION));   
            }
            if(_number > -1)
            sprintf(_caption,"%s %d",_caption,number);
            for(orxOBJECT* obj = orxObject_GetOwnedChild(_mainObject); obj != orxNULL; obj = orxObject_GetOwnedSibling(obj))
		    {
			    const orxSTRING name = orxObject_GetName(obj);
			    if(!orxString_Compare(name,PREVIEW_CAPTION))
			    {
				    _captionObject = obj;
				    orxObject_SetTextString(_captionObject,_caption);
			    }
		    }
        }
    }
    _onlyOnce = false;
    _scale.fX = _scale.fY = 1.2f;
	
}

FFPreview::~FFPreview()
{
	
}

void FFPreview::Update(orxOBJECT* obj)
{
	bool isMoveOn = false;

	if(obj == _mainObject)  
		isMoveOn = true;
	else
	{
		std::vector<orxOBJECT*>::iterator pos;
		pos = find(_listLink.begin(),_listLink.end(),obj);
		if(pos != _listLink.end())
			isMoveOn = true;
	}
	
    if(isMoveOn)
    {
       
        if(_mainObject)
        {
            orxObject_SetScale(_mainObject,&_scale);
        }
        if(!_onlyOnce)
        {
            orxVECTOR pos;
            orxVECTOR size;
            orxObject_GetSize(_mainObject,&size);
            float dx = abs(((size.fX * _scale.fX) - size.fX) / 2);
            float dy = abs(((size.fY * _scale.fY) - size.fY) / 2);
            pos.fX = _position.fX - dx;
            pos.fY = _position.fY - dy; 
            pos.fZ = 1.0;
            orxObject_SetPosition(_mainObject,&pos);
            _onlyOnce = true;
        }
		bool isNew = false;
		bool isLeft = FFInputManager::GetSingleton()->GetInputStatus("MouseLeft",isNew);
		if(isLeft && isNew)
			(_parentForm->*_OnChoose)(_number);
    }
    else
    {
        _onlyOnce = false;
        orxVECTOR scale;
        scale.fX = 1.0;
        scale.fY = 1.0;
        if(_mainObject)
        {
            orxObject_SetScale(_mainObject,&scale);
        }
        orxObject_SetPosition(_mainObject,&_position);
    }
}

void FFPreview::SetScale(orxVECTOR* scale)
{
    _scale.fX = scale->fX;
    _scale.fY = scale->fY;
}

bool FFPreview::LinkObject(orxOBJECT* obj)
{
	if(!obj) // only 2 objects can be linked
		return false;
	orxOBJECT* plastChild = NULL;
	if(!_listLink.size())
	{
		plastChild = _captionObject;
	}
	else if(_listLink.size() == 1)
	{
		plastChild = _listLink.at(0);
	}
	_listLink.push_back(obj);

	orxVECTOR vec = _position;
	vec.fZ = 0.0f;

	orxObject_SetOwner(obj,plastChild);
	orxObject_SetPosition(obj,&vec);

	return true;
}


bool FFPreview::UnlinkObject(orxOBJECT* obj)
{
	if(!obj || _listLink.size() == 0)
		return false;

	std::vector<orxOBJECT*>::iterator pos;
	pos = find(_listLink.begin(),_listLink.end(),obj);
	if(pos != _listLink.end())
		_listLink.erase(pos);

	orxObject_SetOwner(obj,orxNULL);
	if(_listLink.size() == 1)
		orxObject_SetOwner(_listLink.at(0),_captionObject);
	return true;
}

template<typename T>
void FFPreview::remove(std::vector<T>* vec, size_t pos)
{
	std::vector<T>::iterator it = vec->begin();
	std::advance(it,pos);
	vec->erase(it);
}