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


class SceneEvent
{
public:
	SceneEvent(FF_UI_EVENT ev, FFBaseManager* manager, FFScene* scene)
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

	FFBaseManager*	GetManager() {return _gameManager;}
	FFScene*		GetScene()	{return _scene;}
	FF_UI_EVENT		GetEvent() {return _event;}

private:
	FF_UI_EVENT		_event;
	FFBaseManager*	_gameManager;
	FFScene*		_scene;
};


#endif //__FFSCENE_H__