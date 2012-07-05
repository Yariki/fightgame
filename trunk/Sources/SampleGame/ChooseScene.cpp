#include "ChooseScene.h"

#define BEGIN_X -375.0
#define BEGIN_Y -225.0

#define DELTA_X 150.0
#define DELTA_Y 150.0


ChooseScene::ChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
    :FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;
	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			_arrPreview[i][j] =  NULL;
		}
	}
}


ChooseScene::~ChooseScene(void)
{
	Unload();
}


orxSTATUS ChooseScene::Load()
{
    InitializeComponent();
	OnShow();
    return orxSTATUS_SUCCESS;
}

orxSTATUS ChooseScene::Unload()
{
	for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
			if(_arrPreview[i][j])
            {
				delete _arrPreview[i][j];
                _arrPreview[i][j] = NULL;
            }
		}
	}
	for(size_t i = 0; i < _listButton.size(); i++)
	{
		delete _listButton.at(i);
	}
	_listButton.clear();
    return orxSTATUS_SUCCESS;
}

orxSTATUS ChooseScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
		for(int i = 0; i < COLS; i++)
		{
			for(int j = 0; j < ROWS; j++)
			{
				_arrPreview[i][j]->Update(obj);
			}
		}
		for(size_t i = 0; i < _listButton.size(); i++)
		{
			_listButton.at(i)->Update(obj);
		}
	}
    return orxSTATUS_SUCCESS;
}

void ChooseScene::InitializeComponent()
{
	if(orxConfig_Load("../Data/Ini/StaticObject.ini") == orxSTATUS_SUCCESS)
	{
		orxVECTOR pos;
		pos.fX = BEGIN_X;
		pos.fY = BEGIN_Y;
		pos.fZ = 0.0;
		for(int i = 0; i < COLS; i++)
		{
			for(int j = 0; j < ROWS; j++)
			{
				_arrPreview[i][j] = new FFPreview(NULL,pos,NULL);
				pos.fX += DELTA_X;
			}
			pos.fX = BEGIN_X;
			pos.fY += DELTA_Y;
		}
		if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
		{
			pos.fX = -75.0;
			pos.fY += 50.0;
			FFButton* btn = new FFButton(this,pos,"Back",(BUTTONCLICK)&ChooseScene::OnBackClick);
			_listButton.push_back(btn);
            orxVECTOR scale;
            scale.fX = 0.5;
            scale.fY = 1.0;
            pos.fX = -515;
            pos.fY = -10;
            btn = new FFButton(this,pos,"<<<",NULL);
            btn->SetScale(&scale);
            _listButton.push_back(btn);
            pos.fX = 400;
            btn = new FFButton(this,pos,">>>",NULL);
            btn->SetScale(&scale);
            _listButton.push_back(btn);

		}
	}
}

void ChooseScene::ShowGUI()
{
    for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
            _arrPreview[i][j]->Show();
		}
	}
	for(size_t i = 0; i < _listButton.size(); i++)
	{
        _listButton.at(i)->Show();
	}
}

void ChooseScene::HideGUI()
{
    for(int i = 0; i < COLS; i++)
	{
		for(int j = 0; j < ROWS; j++)
		{
            _arrPreview[i][j]->Hide();
		}
	}
	for(size_t i = 0; i < _listButton.size(); i++)
	{
        _listButton.at(i)->Hide();
	}
}

void ChooseScene::OnShow()
{
	SceneEvent ev(FFUE_UI_SCENE_SHOW,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void ChooseScene::OnClose()
{
	SceneEvent ev(FFUE_UI_SCENE_CLOSE,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}


void ChooseScene::OnBackClick()
{
    HideGUI();
	OnClose();
}

void ChooseScene::OnLeftClick()
{

}

void ChooseScene::OnRightClick()
{
    
}