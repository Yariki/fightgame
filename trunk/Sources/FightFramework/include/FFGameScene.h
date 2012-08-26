#ifndef __FFGAMESCENE_H__
#define __FFGAMESCENE_H__ 



#include "FFScene.h"
#include "FFMovableAnimatedObject.h"
#include "FFStaticAnimatedObject.h"
#include "FFStaticObject.h"
#include "FFDynamicObject.h"
#include "FFDynamicAnimatedObject.h"
#include "FFPhysicsWorld.h"



class FFGameScene: public FFScene
{
protected:
	FFMovableAnimatedObject*				_firstHero;
	FFMovableAnimatedObject*				_secondHero;
	std::vector<FFStaticObject*>			_listStaticEntity;
	std::vector<FFStaticAnimatedObject*>	_listStaticAnimEntity;
	std::vector<FFDynamicObject*>			_listDynamicEntity;
	std::vector<FFDynamicAnimatedObject*>	_listDynamicAnimEntity;
	std::string _filePreview;

	FFPhysicsWorld*							_physWorld;

public:
	FFGameScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename);
	virtual ~FFGameScene(void);

public:
	orxSTATUS				Load();
	orxSTATUS				Unload();
	orxSTATUS				Update(const orxCLOCK_INFO* pClockInfo);

	std::string GetPreviewFileName() { return _filePreview;}
	void SetHero(FFMovableAnimatedObject* hero, FF_HERO id);
	

protected:
	bool					LoadStatic(const TiXmlElement* root);
	bool					LoadStaticAnimatedObject(const TiXmlElement* root);
	bool					LoadDynamicObject(const TiXmlElement* root);
	bool					LoadDynamicAnimatedObject(const TiXmlElement* root);

private:
	void OnShow();
	void OnClose();

	void CheckPreview();
};

#endif //__FFGAMESCENE_H__