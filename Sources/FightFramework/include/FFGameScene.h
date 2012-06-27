#ifndef __FFGAMESCENE_H__
#define __FFGAMESCENE_H__ 



#include "FFScene.h"
#include "FFMovableAnimatedObject.h"
#include "FFStaticAnimatedObject.h"
#include "FFStaticObject.h"
#include "FFDynamicObject.h"
#include "FFDynamicAnimatedObject.h"



class FFGameScene: public FFScene
{
protected:
	FFMovableAnimatedObject*				_firstHero;
	FFMovableAnimatedObject*				_secondHero;
	std::vector<FFStaticObject*>			_listStaticEntity;
	std::vector<FFStaticAnimatedObject*>	_listStaticAnimEntity;
	std::vector<FFDynamicObject*>			_listDynamicEntity;
	std::vector<FFDynamicAnimatedObject*>	_listDynamicAnimEntity;

public:
	FFGameScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename);
	virtual ~FFGameScene(void);

public:
	orxSTATUS				Load();
	orxSTATUS				Unload();
	orxSTATUS				Update(const orxCLOCK_INFO* pClockInfo);

protected:
	bool					LoadStatic(const TiXmlElement* root);
	bool					LoadStaticAnimatedObject(const TiXmlElement* root);
	bool					LoadDynamicObject(const TiXmlElement* root);
	bool					LoadDynamicAnimatedObject(const TiXmlElement* root);

private:
	void OnShow(){}
	void OnClose(){}
};

#endif //__FFGAMESCENE_H__