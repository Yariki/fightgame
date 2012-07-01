#ifndef __FFBASEMANAGER_H__
#define __FFBASEMANAGER_H__

#include "FFInclude.h"
#include "FFScene.h"
#include "FFGameScene.h"
#include "FFBaseUiScene.h"




class FFBaseManager
{
protected:
	FFScene*					_currentScene;
	FFScene*					_mainScene;

	std::vector<FFGameScene*>	_listScene;
	std::vector<FFBaseUiScene*> _listUiScene;

	std::stack<FFScene* > _listActiveScene;

	orxSTRING			_fileConfigName;

public:
	FFBaseManager(void);
	virtual ~FFBaseManager(void);


public:
	virtual orxSTATUS Load() = 0;
	virtual orxSTATUS Update(const orxCLOCK_INFO* pstClock) = 0;
	virtual orxSTATUS UserEventHandler(const orxEVENT* pEvent) = 0;
	virtual void LoadCurrentGameScene() = 0;
};


#endif //__FFBASEMANAGER_H__