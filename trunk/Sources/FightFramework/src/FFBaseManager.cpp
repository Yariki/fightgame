#include "FFBaseManager.h"

FFBaseManager::FFBaseManager() 
{
	_uiSceneManager = new FFSceneManager<FFBaseUiScene*>();
	_currentScene = NULL;
}

FFBaseManager::~FFBaseManager()
{
	if(_uiSceneManager)
	{
		delete _uiSceneManager;
		_uiSceneManager = NULL;
	}

}

bool FFBaseManager::IsUIScenePresent(string type)
{
	if(_uiSceneManager) 
		return _uiSceneManager->IsPresentObjectOfType(type);
	else 
		return false;
}

FFBaseUiScene* FFBaseManager::GetUiScene(string type)
{
	if(_uiSceneManager)
		return _uiSceneManager->GetObjectType(type);
	else
		return NULL;
}

void FFBaseManager::AddUiScene(FFBaseUiScene* scene)
{
	if(_uiSceneManager)
	{
		_uiSceneManager->AddObjectType(scene);
	}
}