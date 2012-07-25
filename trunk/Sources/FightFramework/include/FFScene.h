#ifndef __FFSCENE_H__
#define __FFSCENE_H__

#include "FFInclude.h"

class FFBaseManager;

class FFScene
{
protected:
	orxCHAR			_nameCfngFile[MAX_FILE_PATH];
	FF_SCENE_TYPE		_type;
	FF_DISPLAY_SIZE		_sizeDisplay;
	FFBaseManager*		_gameManager;


public:
	FFScene(FFBaseManager* gameManager);
	FFScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size);
	FFScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename);
	virtual ~FFScene(void);

public:
	virtual orxSTATUS		Load() = 0;
	virtual orxSTATUS		Unload() = 0;
	virtual orxSTATUS		Update(const orxCLOCK_INFO* pClockInfo) = 0;

	FF_SCENE_TYPE			SceneType();

private:
	virtual void			OnShow() = 0;
	virtual void			OnClose() = 0;

};


class BaseEvent
{
public:
	BaseEvent(FF_UI_EVENT  ev)
	{
		_event = ev;
	}
	virtual ~BaseEvent(){}

	FF_UI_EVENT GetEvent() { return  _event;}

protected:
	FF_UI_EVENT _event;
};


class SceneEvent : public BaseEvent
{
public:
	SceneEvent(FF_UI_EVENT ev, FFBaseManager* manager, FFScene* scene)
		:BaseEvent(ev)
	{
		
		_gameManager = manager;
		_scene = scene;
	}
	virtual ~SceneEvent()
	{
		_gameManager = NULL;
		_scene = NULL;
	}

	FFBaseManager*	GetManager() {return _gameManager;}
	FFScene*		GetScene()	{return _scene;}
	
protected:
	FFBaseManager*	_gameManager;
	FFScene*		_scene;
};

class ChooseHeroEvent : public BaseEvent
{
public:
	ChooseHeroEvent(FF_UI_EVENT ev,int arg) 
		:BaseEvent(ev)
	{
		_heroIndex = arg;
	}
	virtual ~ChooseHeroEvent() {}

	int GetHeroIndex() {return _heroIndex;}

protected:
	int _heroIndex;

};

class ChooseGameSceneEvent : public ChooseHeroEvent
{
public:
	ChooseGameSceneEvent(FF_UI_EVENT ev, int arg)
		:ChooseHeroEvent(ev,arg)
	{}
	virtual ~ChooseGameSceneEvent(){}
};

#endif //__FFSCENE_H__