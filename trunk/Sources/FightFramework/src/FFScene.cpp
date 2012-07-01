#include "FFScene.h"


FFScene::FFScene(FFBaseManager* gameManager)
	:_gameManager(gameManager)
{
}

FFScene::FFScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size)
	:_gameManager(gameManager),_sizeDisplay(size)
{
}

FFScene::FFScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename)
	:_gameManager(gameManager),_sizeDisplay(size)
{
	orxString_Copy(_nameCfngFile,filename);
}

FFScene::~FFScene(void)
{
}

FF_SCENE_TYPE FFScene::SceneType()
{
	return _type;
}