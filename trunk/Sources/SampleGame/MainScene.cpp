
#include "orx.h"

#include "MainScene.h"
#include "OptionsScene.h"

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
	if(_btnStart)
	{
		delete _btnStart;
		_btnStart = NULL;
	}
	if(_btnChooseScene)
	{
		delete _btnChooseScene;
		_btnChooseScene = NULL;
	}
	if(_btnConfig)
	{
		delete _btnConfig;
		_btnConfig= NULL;
	}
	if(_btnExit)
	{
		delete _btnExit;
		_btnExit = NULL;
	}
	if(_btnChooseHero)
	{
		delete _btnChooseHero;
		_btnChooseHero = NULL;
	}
	return orxSTATUS_SUCCESS;
}

orxSTATUS MainScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
		if(_btnStart)
			_btnStart->Update(obj);
		if(_btnChooseScene)
			_btnChooseScene->Update(obj);
		if(_btnConfig)
			_btnConfig->Update(obj);
		if(_btnExit)
			_btnExit->Update(obj);
		if(_btnChooseHero)
			_btnChooseHero->Update(obj);
	}

	return orxSTATUS_SUCCESS;
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
		_btnStart = new FFButton(this,position,"Start",(BUTTONCLICK)&MainScene::OnStartClick);
		position.fY += delta;
		_btnChooseScene = new FFButton(this,position,"Choose scene",(BUTTONCLICK)&MainScene::OnChooseSceneClick);
		position.fY += delta;
		_btnChooseHero = new FFButton(this,position,"Choose hero",NULL);
		position.fY += delta;
		_btnConfig = new FFButton(this,position,"Options",(BUTTONCLICK)&MainScene::OnConfigClick);
		position.fY += delta;
		_btnExit =  new FFButton(this,position,"Exit",(BUTTONCLICK)&MainScene::OnExitClick);
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
	_btnStart->Show();
	orxLOG("Choose scene CLICK!!!!");
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
	_btnStart->Show();
	_btnChooseScene->Show();
	_btnChooseHero->Show();
	_btnConfig->Show();
	_btnExit->Show();
}

void MainScene::HideGUI()
{
	_btnStart->Hide();
	_btnChooseScene->Hide();
	_btnChooseHero->Hide();
	_btnConfig->Hide();
	_btnExit->Hide();
}
