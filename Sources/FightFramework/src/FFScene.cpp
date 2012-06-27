#include "FFScene.h"


FFScene::FFScene(FFGameManager* gameManager)
	:_gameManager(gameManager)
{
}

FFScene::FFScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size)
	:_gameManager(gameManager),_sizeDisplay(size)
{
}

FFScene::FFScene(FFGameManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename)
	:_gameManager(gameManager),_sizeDisplay(size),_nameCfngFile(filename)
{
}

FFScene::~FFScene(void)
{
}

FF_SCENE_TYPE FFScene::SceneType()
{
	return _type;
}