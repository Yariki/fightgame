
#include "FFGameManager.h"

#define MAIN_GAME_FILE "MainGame.xml"


FFGameManager::FFGameManager(void)
{
	_fileConfigName = MAIN_GAME_FILE;
}

FFGameManager::~FFGameManager(void)
{
	delete _mainScene;
	for(unsigned int i = 0; i < _listScene.size(); i++)
	{
		delete _listScene.at(i);
	}
	_listScene.clear();
}


orxSTATUS FFGameManager::Load()
{
	TiXmlDocument doc;
	bool ok = doc.LoadFile(_fileConfigName);
	if(!ok)
		return orxSTATUS_FAILURE;

	const TiXmlElement* root = doc.RootElement();
	if(!root)
		return orxSTATUS_FAILURE;

	LoadGameScene(root);
	LoadMainScene(root);




	return orxSTATUS_SUCCESS;
}

orxSTATUS FFGameManager::Update(const orxCLOCK_INFO* pstClock)
{
	if(_mainScene)
	{
		_mainScene->Update(pstClock);
	}
	return orxSTATUS_SUCCESS;
}


bool FFGameManager::LoadGameScene(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* gamescene = root->FirstChildElement(FF_MANAGER_GAMESCENES);
	if(gamescene)
	{
		FF_DISPLAY_SIZE size = {0};
		orxDisplay_GetScreenSize(&size._Width,&size._Height);
		size._Top =  - size._Height / 2.0f;
		size._Left = - size._Width / 2.0f;
		size._Bottom = - size._Top;
		size._Right = - size._Left;
		for(const TiXmlElement* node = gamescene->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_MANAGER_FILENAMESCENE_ATTRIBUTE));
			FFGameScene* scene = new FFGameScene(this,size,filename);
			_listScene.push_back(scene);
		}
		res = true;
	}

	return res;
}


bool FFGameManager::LoadMainScene(const TiXmlElement* root)
{
	bool res = false;
	orxCHAR filemainScene[MAX_FILE_PATH]; 
	orxString_Copy(filemainScene, root->Attribute(FF_MANAGER__MAINSCENE_ATTRIBUTE));
	FF_DISPLAY_SIZE size = {0};
	orxDisplay_GetScreenSize(&size._Width,&size._Height);
	size._Top =  - size._Height / 2.0f;
	size._Left = - size._Width / 2.0f;
	size._Bottom = - size._Top;
	size._Right = - size._Left;

	FFGameScene* main = new FFGameScene(this,size,filemainScene);
	main->Load();
	_mainScene = main;
	main = NULL;

	return true;
}
