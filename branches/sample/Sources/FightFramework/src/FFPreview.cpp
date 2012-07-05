#include "FFPreview.h"

FFPreview::FFPreview(FFBaseUiScene* parent,orxVECTOR& position, orxCHAR* name)
    :FFBaseControl(parent,position,name)
{
    //_OnChoose = onchoose != NULL ? onchoose : NULL;
    _mainObject = orxObject_CreateFromConfig(PREVIEW_SECTION);
    //_graphic = orxNULL;
    if(_mainObject)
    {
        orxObject_SetPosition(_mainObject,&_position);
        if(orxConfig_PushSection(PREVIEW_SECTION) == orxSTATUS_SUCCESS)
        {
            orxString_Copy(_caption,orxConfig_GetString(PREVIEW_CAPTION));   
        }
    }
    _onlyOnce = false;
    _scale.fX = _scale.fY = 1.2;

}

FFPreview::~FFPreview()
{
}

void FFPreview::Update(orxOBJECT* obj)
{
    if(obj == _mainObject)
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
            pos.fZ = 0.0;
            orxObject_SetPosition(_mainObject,&pos);
            _onlyOnce = true;
        }
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