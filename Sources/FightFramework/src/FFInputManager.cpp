
#include "FFInputManager.h"
#include "FFPlayerController.h"


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
	// create first controller
	_controllers[CONTROLLER1] = new FFPlayerController(FFCI_FIRST,FFInputManager::GetSingleton());
	// create secont controller 
	_controllers[CONTROLLER2] = new FFPlayerController(FFCI_SECOND,FFInputManager::GetSingleton());


	return status == orxSTATUS_SUCCESS ? true : false;
}

void FFInputManager::UnloadSettings()
{
	for(int i = 0; i < 2;i++)
	{
		delete _controllers[i];
		_controllers[i] = NULL;
	}
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


FFBaseController* FFInputManager::GetPlayerController(FF_CONTROLLER_ID id)
{
	switch(id)
	{
	case FFCI_FIRST:
		return _controllers[CONTROLLER1];
	case FFCI_SECOND:
		return _controllers[CONTROLLER2];
	}
	return NULL;
}