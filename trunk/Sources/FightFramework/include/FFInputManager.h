#ifndef __FFINPUTMAMNAGER_H__
#define __FFINPUTMAMNAGER_H__

#include "FFInclude.h"
#include "FFVector3.h"
#include "FFBaseController.h"
#define CONTROLLER1 0
#define CONTROLLER2 1




class FFInputManager
{
protected:
	FFInputManager(void);
	FFInputManager(const FFInputManager&);
	FFInputManager& operator=(const FFInputManager&);
	
	FFBaseController* _controllers[2];

	virtual ~FFInputManager();

private:
	static FFInputManager*	_inputManager;
	static bool				_isLoaded;

public:
	static FFInputManager*	GetSingleton();
	static void				LoadInputSettings();


public:
	
	bool					LoadSettings();
	bool					GetInputStatus(orxCHAR* key, bool& newState);
	void					GetMousePosition(FFVector3* position);
	FFBaseController*		GetPlayerController(FF_CONTROLLER_ID id);
	void					UnloadSettings();

};




#endif