#include "FFStaticObject.h"
#include "FFDefines.h"

FFStaticObject::FFStaticObject(void)
{
	_type = FFSOT_STATIC;
}

FFStaticObject::FFStaticObject(orxSTRING filename)
	:FFObject(filename)
{
	_type = FFSOT_STATIC;
}


FFStaticObject::~FFStaticObject(void)
{
}

void FFStaticObject::Create()
{
	if(std::string(_nameCfgFile).length() > 0)
	{
		if(orxConfig_Load(_nameCfgFile) == orxSTATUS_SUCCESS)
		{
			switch(_type)
			{
			case FFSOT_STATIC:
				_object = orxObject_CreateFromConfig(FF_STATIC_OBJECT_SECTION_NAME);
				if(orxConfig_PushSection(FF_STATIC_OBJECT_SECTION_NAME) == orxSTATUS_SUCCESS)
				{
					orxCHAR temp[MAX_FILE_PATH];
					orxString_Copy(temp, orxConfig_GetString(ENTITY_TYPE_SECTION));
					if(!orxString_Compare(temp,ENTITY_TYPE_WALL_VALUE))
						_typeEntity = FTE_STATIC;

					orxVECTOR a;
					orxConfig_GetVector(FF_POSITION,&a);
					_position = a;
					orxConfig_GetVector(FF_SPEED,&a);
					_speed = a;

					orxConfig_PopSection();
				}
				break;
			case FFSOT_ANIMATED:
				_object = orxObject_CreateFromConfig(FF_STATIC_ANIMATED_OBJECT_SECTION_NAME);
				break;
			}
			orxConfig_Clear();
			orxObject_SetUserData(_object,this);
			UpdateAABox();
		}
	}
}

void FFStaticObject::UpdatePhysics(float deltaTime)
{
	//UpdateAABox();
}

void FFStaticObject::UpdateAABox()
{
	__super::UpdateAABox();
	float x = 1.0;
	float y = 1.0;
	orxVECTOR scale;
	orxVECTOR size;
	orxObject_GetScale(_object,&scale);
	orxObject_GetSize(_object,&size);
	if(scale.fX > 0.0)
		_aabox.vBR.fX += (size.fX * scale.fX);
	if(scale.fY > 0.0)
		_aabox.vBR.fY += (size.fY * scale.fY);
}
