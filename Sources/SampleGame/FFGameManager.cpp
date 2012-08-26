
#include "FFGameManager.h"
#include "MainScene.h"


#define MAIN_GAME_FILE "MainGame.xml"
#define IMAGE_PREVIEW  "Preview"


FFGameManager::FFGameManager(void)
	:FFBaseManager()
{
	_fileConfigName = MAIN_GAME_FILE;
	_indexFirstHero = _indexSecondHero = _indexGameScene = -1;
}

FFGameManager::~FFGameManager(void)
{
	if(_mainScene)
	{
		delete _mainScene;
	}
	_listFileScene.clear();
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
	LoadHeroes(root);




	return orxSTATUS_SUCCESS;
}

orxSTATUS FFGameManager::Update(const orxCLOCK_INFO* pstClock)
{
	
	if(_listActiveScene.size() > 0)
	{
		_listActiveScene.top()->Update(pstClock);		
	}
	else if(_currentScene)
	{
		_currentScene->Update(pstClock);
	}
	else if(_mainScene)
	{
		_mainScene->Update(pstClock);
	} 

	if(_listForDelete.size() > 0)
	{
		for(size_t i = 0; i < _listForDelete.size(); i++)
		{
			FFScene* scene = _listForDelete.at(i);
			if(scene->SceneType() == FFST_UISCENE)
				scene->Unload();
			else if(scene->SceneType() == FFST_GAMESCENE)
				delete scene;
			scene = NULL;
		}
		_listForDelete.clear();
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
			FFGameScene* gscene = new FFGameScene(this,size,filename);
			_listFileScene.push_back(gscene);
		}
		res = true;
	}

	return res;
}


bool FFGameManager::LoadHeroes(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* heroes = root->FirstChildElement(FF_MANAGER_HEROS);
	if(heroes)
	{
		for(const TiXmlElement* node = heroes->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_MANAGER_FILENAMESCENE_ATTRIBUTE));
			// TODO: now we just read preview file name from file settings, in future 
			// we should create class Hero, and add to this class method which will call "GetPreviewFileName"
			TiXmlDocument doc;
			bool isLoad = doc.LoadFile(filename);
			if(isLoad)
			{
				const TiXmlElement* root = doc.RootElement();
				if(!root)
					continue;
				orxString_Copy(filename,root->Attribute(IMAGE_PREVIEW));
				if(orxString_GetLength(filename))
					_listHeroPreview.push_back(std::string(filename));
				for(const TiXmlElement* elHero = root->FirstChildElement(); elHero; elHero = elHero->NextSiblingElement())
				{
					orxString_Copy(filename,elHero->Attribute(FF_MANAGER_FILENAMESCENE_ATTRIBUTE));
					if(orxString_GetLength(filename))
						_listHero.push_back(std::string(filename));
				}
			}
			
		}
		res = true;
	}
	return res;
}

bool FFGameManager::LoadMainScene(const TiXmlElement* root)
{
	FF_DISPLAY_SIZE size = {0};
	orxDisplay_GetScreenSize(&size._Width,&size._Height);
	size._Top =  - size._Height / 2.0f;
	size._Left = - size._Width / 2.0f;
	size._Bottom = - size._Top;
	size._Right = - size._Left;


	MainScene* scene = new MainScene(this,size);
	scene->Load();
	_mainScene = scene;
	scene = NULL;

	return true;
}

orxSTATUS FFGameManager::UserEventHandler(const orxEVENT* pEvent)
{
	BaseEvent* ev = static_cast<BaseEvent*>(pEvent->pstPayload);

	switch(ev->GetEvent())
	{
		case FFUE_UI_SCENE_SHOW:	
			{
				SceneEvent* e = static_cast<SceneEvent*>(pEvent->pstPayload);						
				orxLOG("FFUE_UI_SCENE_SHOW");
				_currentScene = e->GetScene();
			}
			break;
		case FFUE_UI_SCENE_CLOSE:	
			{
				SceneEvent* e = static_cast<SceneEvent*>(pEvent->pstPayload);
				orxLOG("FFUE_UI_SCENE_CLOSE");
				FFBaseUiScene* active = static_cast<FFBaseUiScene*>(e->GetScene());
				_currentScene = NULL;
				_listForDelete.push_back(active);
				((FFBaseUiScene*)_mainScene)->Load();
			}
			break;
		case FFUE_GAME_SCENE_SHOW:
			{
				SceneEvent* e = static_cast<SceneEvent*>(pEvent->pstPayload);
				orxLOG("FFUE_GAME_SCENE_SHOW");
				_listActiveScene.push(e->GetScene());
			}
			break;
		case FFUE_GAME_SCENE_CLOSE:
			orxLOG("FFUE_GAME_SCENE_CLOSE");
			if(_listActiveScene.size() > 0)
			{
				FFScene* active = _listActiveScene.top();
				_listActiveScene.pop();
				_listForDelete.push_back(active);
				if(_listActiveScene.empty() && _mainScene->SceneType() == FFST_UISCENE)
				{
					((FFBaseUiScene*)_mainScene)->Load();
				}
				else
				{
					FFScene* next = _listActiveScene.top();
					if(next->SceneType() == FFST_UISCENE)
					{
						((FFBaseUiScene*)next)->Load();
					}
				}
			}
			break;
		case FFUE_FIRST_HERO_CHOOSE:
			{
				ChooseHeroEvent* heroEv = static_cast<ChooseHeroEvent*>(pEvent->pstPayload);
				_indexFirstHero = heroEv->GetHeroIndex();
				orxLOG("CHOOSE FIRST HERO - %d",_indexFirstHero);
			}
			break;
		case FFUE_SECOND_HERO_CHOOSE:
			{
				ChooseHeroEvent* heroEv = static_cast<ChooseHeroEvent*>(pEvent->pstPayload);
				_indexSecondHero = heroEv->GetHeroIndex();
				orxLOG("CHOOSE SECOND HERO - %d",_indexSecondHero);
			}
			break;
		case FFUE_GAME_SCENE_CHOOSE:
			{
				ChooseGameSceneEvent* e = static_cast<ChooseGameSceneEvent*>(pEvent->pstPayload);
				_indexGameScene  = e->GetHeroIndex();
				orxLOG("CHOOSE GAME SCENE - %d",_indexGameScene);
			}
			break;

	}

	return orxSTATUS_SUCCESS;
}


void FFGameManager::LoadCurrentGameScene()
{
	if(_listFileScene.size() > 0)
	{
		((FFBaseUiScene*)_mainScene)->Unload();
		FFGameScene* scene = _listFileScene.at(0);
		scene->Load();
		if(_indexFirstHero < _listHero.size())
		{

			FFMovableAnimatedObject* hero = new FFMovableAnimatedObject((orxCHAR*)_listHero.at(_indexFirstHero).c_str());
			scene->SetHero(hero,FFH_FIRST);
		}
	}
}