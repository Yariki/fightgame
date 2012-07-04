#include "OptionsScene.h"

#define CHOOSEBTN_DELTA_FOR_CHILD 27.0f

OptionsScene::OptionsScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
	:FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;
	
}


OptionsScene::~OptionsScene(void)
{
	Unload();
}

orxSTATUS OptionsScene::Load()
{
	
	InitializeComponent();
	OnShow();
	
	return orxSTATUS_SUCCESS;
}

orxSTATUS OptionsScene::Unload()
{
	size_t i;
	for( i =0; i < _listChecks.size(); i++)
	{
		delete _listChecks.at(i);
	}
	for( i =0; i < _listCombo.size(); i++)
	{
		delete _listCombo.at(i);
	}
	delete _btnBack;
	_btnBack = NULL;
	_listCombo.clear();
	_listChecks.clear();

	return orxSTATUS_SUCCESS;
}

orxSTATUS OptionsScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
		size_t i;
		for( i =0; i < _listChecks.size(); i++)
		{
			_listChecks.at(i)->Update(obj);
		}
		for( i =0; i < _listCombo.size(); i++)
		{
			_listCombo.at(i)->Update(obj);
		}
		_btnBack->Update(obj);
	}
	return orxSTATUS_SUCCESS;
}

void OptionsScene::InitializeComponent()
{
	orxVECTOR position;
	position.fX = -75.0f;
	position.fY = -150.0f;
	position.fZ = 0.0f;
	float delta = 50.0f;
	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
		FFCheckBox* check = new FFCheckBox(this,position,"Fullscreen",NULL);
		_listChecks.push_back(check);
		position.fY += delta;
		check = new FFCheckBox(this,position,"Use BLOOM",NULL);
		_listChecks.push_back(check);
		position.fY += delta;
		position.fX += CHOOSEBTN_DELTA_FOR_CHILD;
		FFComboChooseButton* combo = new FFComboChooseButton(this,position,"n/a",NULL);
		combo->AddItem("800 X 600");
		combo->AddItem("1024 X 768");
		combo->AddItem("1280 X 720");
		combo->AddItem("1920 X 1080");
		_listCombo.push_back(combo);
		position.fX -= CHOOSEBTN_DELTA_FOR_CHILD;
		position.fY += 2 * delta;
		_btnBack = new FFButton(this,position,"Back",(BUTTONCLICK)&OptionsScene::OnBackClick);
	}
}

void OptionsScene::OnShow()
{
	SceneEvent ev(FFUE_UI_SCENE_SHOW,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void OptionsScene::OnClose()
{
	SceneEvent ev(FFUE_UI_SCENE_CLOSE,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void OptionsScene::HideGUI()
{
	size_t i;
	for( i =0; i < _listChecks.size(); i++)
	{
		_listChecks.at(i)->Hide();
	}
	for( i =0; i < _listCombo.size(); i++)
	{
		_listCombo.at(i)->Hide();
	}
	_btnBack->Hide();
}

void OptionsScene::ShowGUI()
{
	size_t i;
	for( i =0; i < _listChecks.size(); i++)
	{
		_listChecks.at(i)->Show();
	}
	for( i =0; i < _listCombo.size(); i++)
	{
		_listCombo.at(i)->Show();
	}
	_btnBack->Show();
}


void OptionsScene::OnBackClick()
{
	HideGUI();
	OnClose();
}
