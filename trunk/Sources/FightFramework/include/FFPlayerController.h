#ifndef __FFPLAYERCONTROLLER_H__
#define __FFPLAYERCONTROLLER_H__

#include "FFInputManager.h"
#include "FFBaseController.h"

class FFPlayerController : public FFBaseController
{
protected:
	orxCHAR	_walkRight[MAX_KEY_NAME];
	orxCHAR	_walkLeft[MAX_KEY_NAME];
	orxCHAR	_jump[MAX_KEY_NAME];
	orxCHAR	_down[MAX_KEY_NAME];

	FFInputManager* _inputMahager;

public:
	FFPlayerController(FF_CONTROLLER_ID id, FFInputManager* manager);
	virtual ~FFPlayerController();
		
	virtual bool IsUp(bool& isNew);
	virtual bool IsDown(bool& isNew);
	virtual bool IsRight(bool& isNew);
	virtual bool IsLeft(bool& isNew);

private:
	bool CheckInput(const orxCHAR* key, bool& isNew);
};


#endif //__FFPLAYERCONTROLLER_H__