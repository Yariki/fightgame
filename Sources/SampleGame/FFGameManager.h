#ifndef __FFGAMEMANAGER_H__
#define __FFGAMEMANAGER_H__


#include "FFBaseManager.h"


class FFGameManager : public FFBaseManager
{

protected:
	std::vector<FFScene*> _listForDelete;
	int _indexFirstHero;
	int _indexSecondHero;
	int _indexGameScene;


public:
	FFGameManager(void);
	virtual ~FFGameManager(void);
	

public:
	virtual orxSTATUS Load();
	virtual orxSTATUS Update(const orxCLOCK_INFO* pstClock);
	virtual orxSTATUS UserEventHandler(const orxEVENT* pEvent);
	virtual void LoadCurrentGameScene();

protected:
	bool LoadGameScene(const TiXmlElement* root);
	bool LoadUIScene(const TiXmlElement* root);
	bool LoadMainScene(const TiXmlElement* root);
	bool LoadHeroes(const TiXmlElement* root);
};

#endif //__FFGAMEMANAGER_H__