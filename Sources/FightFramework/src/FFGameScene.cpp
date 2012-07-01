#include "FFGameScene.h"
#include "FFInputManager.h"
#define FF_STATIC_OBJECTS					"StaticObjects"
#define FF_STATIC_ANIMATED_OBJECTS			"StaticAnimatedObjects"
#define FF_DYNAMIC_OBJECTS					"DynamicObjects"
#define FF_DYNAMIC_ANIMATED_OBJECTS			"DynamicAnimatedObjects"
#define FF_FILENAME_ATTRIBUTE				"Filename"



FFGameScene::FFGameScene(FFBaseManager* gameManager,FF_DISPLAY_SIZE& size,orxSTRING filename)
	:FFScene(gameManager,size,filename)
{
	_type = FFST_GAMESCENE;
}


FFGameScene::~FFGameScene(void)
{
	Unload();
}


orxSTATUS FFGameScene::Load()
{
	TiXmlDocument doc(_nameCfngFile);
	bool okLoad = doc.LoadFile();
	
	if(!okLoad)
	{
		return orxSTATUS_FAILURE;
	}

	const TiXmlElement* root = doc.RootElement();
	if(!root)
	{
		return orxSTATUS_FAILURE;
	}
	orxConfig_Clear();
	bool staticLoad = LoadStatic(root);
	bool staticAnim = LoadStaticAnimatedObject(root);
	bool dynamicLoad = LoadDynamicObject(root);
	bool dynamicAnim = LoadDynamicAnimatedObject(root);

	if(staticLoad)
	{
		for(unsigned int i = 0; i<_listStaticEntity.size();i++)
		{
			_listStaticEntity.at(i)->Create();
		}
	}

	if(staticAnim)
	{
		for(unsigned int i = 0; i<_listStaticAnimEntity.size();i++)
		{
			_listStaticAnimEntity.at(i)->Create();
		}
	}
	if(dynamicLoad)
	{
		for(unsigned int i = 0; i<_listDynamicEntity.size();i++)
		{
			_listDynamicEntity.at(i)->Create();
		}
	}
	if(dynamicAnim)
	{
		for(unsigned int i = 0; i<_listDynamicAnimEntity.size();i++)
		{
			_listDynamicAnimEntity.at(i)->Create();
		}
	}
	OnShow();
	return orxSTATUS_SUCCESS;
}

orxSTATUS FFGameScene::Unload()
{

	for(unsigned int i = 0 ; i < _listStaticEntity.size(); i++)
	{
		
		delete _listStaticEntity.at(i);
	}
	for(unsigned int i = 0 ; i < _listStaticAnimEntity.size(); i++)
	{
		
		delete _listStaticAnimEntity.at(i);
	}
	for(unsigned int i = 0 ; i < _listDynamicEntity.size(); i++)
	{
		
		delete _listDynamicEntity.at(i);
	}
	for(unsigned int i = 0 ; i < _listDynamicAnimEntity.size(); i++)
	{
		
		delete _listDynamicAnimEntity.at(i);
	}
	_listStaticEntity.clear();
	_listStaticAnimEntity.clear();
	_listDynamicEntity.clear();
	_listDynamicAnimEntity.clear();

	return orxSTATUS_SUCCESS;
}


orxSTATUS FFGameScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	bool isNew;
	bool isPress = FFInputManager::GetSingleton()->GetInputStatus("Escape",isNew);
	if(isPress && isNew)
	{
		OnClose();
		Unload();
		return orxSTATUS_SUCCESS;
	}

	for(unsigned int i = 0; i < _listStaticAnimEntity.size();i++)
	{
		_listStaticAnimEntity.at(i)->Update(pClockInfo);
	}
	for(unsigned int i = 0; i < _listDynamicEntity.size();i++)
	{
		_listDynamicEntity.at(i)->Update(pClockInfo);
	}
	for(unsigned int i = 0; i < _listDynamicAnimEntity.size();i++)
	{
		_listDynamicAnimEntity.at(i)->Update(pClockInfo);
	}

	return orxSTATUS_SUCCESS;
}


bool FFGameScene::LoadStatic(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* staticObjects = root->FirstChildElement(FF_STATIC_OBJECTS);
	if(staticObjects)
	{
		for(const TiXmlElement* node = staticObjects->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_FILENAME_ATTRIBUTE));
			FFStaticObject* obj = new FFStaticObject(filename);
			_listStaticEntity.push_back(obj);
		}
		res = true;
	}
	return res;
}

bool FFGameScene::LoadStaticAnimatedObject(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* staticAnim = root->FirstChildElement(FF_STATIC_ANIMATED_OBJECTS);
	if(staticAnim)
	{
		for(const TiXmlElement* node = staticAnim->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_FILENAME_ATTRIBUTE));
			FFStaticAnimatedObject* obj = new FFStaticAnimatedObject(filename);
			_listStaticAnimEntity.push_back(obj);
		}
		res = true;
	}
	return res;
}


bool FFGameScene::LoadDynamicObject(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* dynamicObjects = root->FirstChildElement(FF_DYNAMIC_OBJECTS);
	if(dynamicObjects)
	{
		for(const TiXmlElement* node = dynamicObjects->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_FILENAME_ATTRIBUTE));
			FFDynamicObject* obj = new FFDynamicObject(filename);
			_listDynamicEntity.push_back(obj);
		}
		res = true;
	}
	return res;
}

bool FFGameScene::LoadDynamicAnimatedObject(const TiXmlElement* root)
{
	bool res = false;
	const TiXmlElement* dynamicAnim = root->FirstChildElement(FF_DYNAMIC_ANIMATED_OBJECTS);
	if(dynamicAnim)
	{
		for(const TiXmlElement* node = dynamicAnim->FirstChildElement(); node ; node = node->NextSiblingElement())
		{
			orxCHAR filename[MAX_FILE_PATH];
			orxString_Copy(filename,node->Attribute(FF_FILENAME_ATTRIBUTE));
			FFDynamicAnimatedObject* obj = new FFDynamicAnimatedObject(filename);
			
			_listDynamicAnimEntity.push_back(obj);
		}
		res = true;
	}
	return res;
}

void FFGameScene::OnShow()
{
	SceneEvent ev(FFUE_GAME_SCENE_SHOW,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void FFGameScene::OnClose()
{
	SceneEvent ev(FFUE_GAME_SCENE_CLOSE,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}