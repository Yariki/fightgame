
#include "FFInputManager.h"

FFInputManager* FFInputManager::_inputManager = orxNULL;
bool FFInputManager::_isLoaded = false;

FFInputManager::FFInputManager()
{

}

FFInputManager::~FFInputManager()
{

}

FFInputManager* FFInputManager::GetSingleton()
{
	if(_inputManager != NULL)
		return _inputManager;
	_inputManager = new FFInputManager();
	return _inputManager;
}

bool FFInputManager::LoadSettings()
{
	orxSTATUS status = orxInput_Load(orxSTRING_EMPTY);
	return status == orxSTATUS_SUCCESS ? true : false;
}


bool FFInputManager::GetInputStatus(orxCHAR* key, bool& newState)
{
	if(!FFInputManager::_isLoaded)
	{
		newState = false;
		return false;
	}

	bool res = false;
	if(orxInput_IsActive(key) && orxInput_HasNewStatus(key))
	{
		newState = true;
		res = true;
	}
	else if(orxInput_IsActive(key))
	{
		newState = false;
		res = true;
	}
	return res;
}

void FFInputManager::GetMousePosition(orxVECTOR* position)
{
	orxMouse_GetPosition(position);
}

void  FFInputManager::LoadInputSettings()
{
	_isLoaded = FFInputManager::GetSingleton()->LoadSettings();
}
