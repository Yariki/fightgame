#ifndef __FFSCENE_H__
#define __FFSCENE_H__

#include "FFInclude.h"

class FFGameManager;

class FFScene
{
protected:
	orxSTRING			_nameCfngFile;
	FF_SCENE_TYPE		_type;
	FF_DISPLAY_SIZE		_sizeDisplay;
	FFGameManager*		_gameManager;


public:
	FFScene(FFGameManager* gameManager);
	FFScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size);
	FFScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename);
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


class SceneEvent
{
public:
	SceneEvent(FF_UI_EVENT ev, FFGameManager* manager, FFScene* scene)
	{
		_event = ev;
		_gameManager = manager;
		_scene = scene;
	}
	virtual ~SceneEvent()
	{
		_gameManager = NULL;
		_scene = NULL;
	}

	FFGameManager*	GetManager() {return _gameManager;}
	FFScene*		GetScene()	{return _scene;}
	FF_UI_EVENT		GetEvent() {return _event;}

private:
	FF_UI_EVENT		_event;
	FFGameManager*	_gameManager;
	FFScene*		_scene;
};


#endif //__FFSCENE_H__