
#include "FFInclude.h"

#include "MainScene.h"
#include "OptionsScene.h"
#include "ChooseScene.h"

MainScene::MainScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
	:FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;
}


MainScene::~MainScene()
{
	Unload();
}


orxSTATUS MainScene::Load()
{
	InitializeComponent();
	return orxSTATUS_SUCCESS;
}

orxSTATUS MainScene::Unload()
{
    for(size_t i = 0; i < _buttons.size(); i++)
    {
        delete _buttons.at(i);
    }
    _buttons.clear();
	return orxSTATUS_SUCCESS;
}

void MainScene::UpdateGUI(orxOBJECT* obj)
{
    for(size_t i = 0; i < _buttons.size(); i++)
    {
        _buttons.at(i)->Update(obj);
    }
}

void MainScene::InitializeComponent()
{
	orxVECTOR position;
	position.fX = -75.0f;
	position.fY = -150.0f;
	position.fZ = 0.0f;
	float delta = 50.0f;
	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
        FFButton* btn = NULL;
		btn = new FFButton(this,position,"Start",(BUTTONCLICK)&MainScene::OnStartClick);
        _buttons.push_back(btn); btn = NULL;
		position.fY += delta;
		btn = new FFButton(this,position,"Choose scene",(BUTTONCLICK)&MainScene::OnChooseSceneClick);
        _buttons.push_back(btn); btn = NULL;
		position.fY += delta;
		btn = new FFButton(this,position,"Choose hero",NULL);
        _buttons.push_back(btn); btn = NULL;
		position.fY += delta; 
		btn = new FFButton(this,position,"Options",(BUTTONCLICK)&MainScene::OnConfigClick);
        _buttons.push_back(btn); btn = NULL;
		position.fY += delta;
		btn =  new FFButton(this,position,"Exit",(BUTTONCLICK)&MainScene::OnExitClick);
        _buttons.push_back(btn); btn = NULL;
	}
}

void MainScene::OnShow()
{
	//SceneEvent ev(FFUE_UI_SCENE_SHOW,_gameManager,this);
	//orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void MainScene::OnClose()
{
	//SceneEvent ev(FFUE_UI_SCENE_CLOSE,_gameManager,this);
	//orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void MainScene::OnStartClick()
{
	//_btnStart->Hide();
	if(_gameManager)
	{
		_gameManager->LoadCurrentGameScene();
	}
	orxLOG("Start CLICK!!!!");
}

void MainScene::OnChooseSceneClick()
{
	orxLOG("Choose scene CLICK!!!!");
	Unload();
	ChooseScene* chooseScene = NULL;
	if(_gameManager->IsUIScenePresent(typeid(ChooseScene).name()))
	{
		chooseScene = static_cast<ChooseScene*>(_gameManager->GetUiScene(typeid(ChooseScene).name()));
	}
	else
	{
		chooseScene = new ChooseScene((FFGameManager*)_gameManager,_sizeDisplay);
		_gameManager->AddUiScene(chooseScene);
	}
	if(chooseScene) 
		chooseScene->Load();
}

void MainScene::OnConfigClick()
{
	orxLOG("Options CLICK!!!!!");
	Unload();
	OptionsScene* optScene = NULL;
	if(_gameManager->IsUIScenePresent(typeid(OptionsScene).name()))
	{
		optScene = static_cast<OptionsScene*>(_gameManager->GetUiScene(typeid(OptionsScene).name()));
	}
	else
	{
		optScene = new OptionsScene((FFGameManager*)_gameManager,_sizeDisplay);
		_gameManager->AddUiScene(optScene);
	}
	if(optScene) 
		optScene->Load();
}

void MainScene::OnExitClick()
{
	// user event for application closing
	SceneEvent ev(FFUE_APPLICATION_CLOSE,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);

	// system event to close application
	orxEVENT_SEND(orxEVENT_TYPE_SYSTEM,orxSYSTEM_EVENT_CLOSE,this,orxNULL,orxNULL);
}

void MainScene::ShowGUI()
{
    for(size_t i = 0; i < _buttons.size(); i++)
    {
        _buttons.at(i)->Show();
    }
}

void MainScene::HideGUI()
{
	for(size_t i = 0; i < _buttons.size(); i++)
    {
        _buttons.at(i)->Hide();
    }
}
