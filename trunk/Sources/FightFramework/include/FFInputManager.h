#ifndef __FFINPUTMAMNAGER_H__
#define __FFINPUTMAMNAGER_H__

#include "FFInclude.h"

class FFInputManager
{
protected:
	FFInputManager(void);
	FFInputManager(const FFInputManager&);
	FFInputManager& operator=(const FFInputManager&);

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
	void					GetMousePosition(orxVECTOR* position);

};




#endif