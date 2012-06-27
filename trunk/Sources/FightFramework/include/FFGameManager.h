#ifndef __FFGAMEMANAGER_H__
#define __FFGAMEMANAGER_H__


#pragma  once

#include "FFInclude.h"
#include "FFScene.h"
#include "FFGameScene.h"
#include "FFBaseUiScene.h"


class FFGameManager
{
protected:
	FFScene*					_currentScene;
	FFScene*					_mainScene;

	std::vector<FFGameScene*>	_listScene;
	std::vector<FFBaseUiScene*> _listUiScene;

	std::stack<FFScene* > _listActiveScene;

	orxSTRING			_fileConfigName;

public:
	FFGameManager(void);
	virtual ~FFGameManager(void);
	

public:
	virtual orxSTATUS Load();
	virtual orxSTATUS Update(const orxCLOCK_INFO* pstClock);
	virtual orxSTATUS UserEventHandler(const orxEVENT* pEvent);

protected:
	bool LoadGameScene(const TiXmlElement* root);
	bool LoadUIScene(const TiXmlElement* root);
	bool LoadMainScene(const TiXmlElement* root);
};

#endif //__FFGAMEMANAGER_H__