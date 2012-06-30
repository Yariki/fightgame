#ifndef __FFGAMEMANAGER_H__
#define __FFGAMEMANAGER_H__


#include "FFBaseManager.h"


class FFGameManager : public FFBaseManager
{

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