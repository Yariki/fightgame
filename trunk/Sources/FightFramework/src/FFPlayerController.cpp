
#include "FFPlayerController.h"

FFPlayerController::FFPlayerController(FF_CONTROLLER_ID id, FFInputManager* manager)
{
	_inputMahager = manager;
	const orxCHAR* nameSection = NULL;
	switch(id)
	{
	case FFCI_FIRST:
		nameSection = CONTROLLER_FIRST;
		break;
	case FFCI_SECOND:
		nameSection = CONTROLLER_SECOND;
		break;
	}
	if(nameSection != NULL && orxConfig_PushSection(nameSection) == orxSTATUS_SUCCESS)
	{
		orxString_Copy(_walkRight, orxConfig_GetString(WALK_RIGHT_SECTION));
		orxString_Copy(_walkLeft, orxConfig_GetString(WALK_LEFT_SECTION));
		orxString_Copy(_down, orxConfig_GetString(DOWN_SECTION));
		orxString_Copy(_jump, orxConfig_GetString(JUMP_SECTION));
	}
}


FFPlayerController::~FFPlayerController()
{
	_inputMahager = NULL;
}


bool FFPlayerController::CheckInput(const orxCHAR* key, bool& isNew)
{
	isNew = false;
	if(!_inputMahager) return false;
	return _inputMahager->GetInputStatus((orxCHAR*)key,isNew);
}

bool FFPlayerController::IsUp(bool& isNew)
{
	return CheckInput(_jump,isNew);
}

bool FFPlayerController::IsDown(bool& isNew)
{
	return CheckInput(_down,isNew);
}

bool FFPlayerController::IsLeft(bool& isNew)
{
	return CheckInput(_walkLeft,isNew);
}

bool FFPlayerController::IsRight(bool& isNew)
{
	return CheckInput(_walkRight,isNew);
}