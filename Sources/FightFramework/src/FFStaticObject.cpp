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
				break;
			case FFSOT_ANIMATED:
				_object = orxObject_CreateFromConfig(FF_STATIC_ANIMATED_OBJECT_SECTION_NAME);
				break;
			}
			//orxConfig_Clear();
			orxObject_SetUserData(_object,this);
		}
	}
}
