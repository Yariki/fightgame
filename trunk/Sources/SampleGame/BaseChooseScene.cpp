#include "BaseChooseScene.h"



#define BTN_LEFT_FILE "../Data/Ini/ButtonsLeft.ini"
#define BTN_RIGHT_FILE "../Data/Ini/ButtonsRight.ini"


BaseChooseScene::BaseChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
    :FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            _arrPreview[i][j]._preview =  NULL;
		}
	}
}


BaseChooseScene::~BaseChooseScene(void)
{
	Unload();
}


orxSTATUS BaseChooseScene::Load()
{
    InitializeComponent();
	OnShow();
    return orxSTATUS_SUCCESS;
}

orxSTATUS BaseChooseScene::Unload()
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            if(_arrPreview[i][j]._preview)
            {
                delete _arrPreview[i][j]._preview;
                _arrPreview[i][j]._preview = NULL;
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

void BaseChooseScene::UpdateGUI(orxOBJECT* obj)
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            if(_arrPreview[i][j]._preview != NULL)
                _arrPreview[i][j]._preview->Update(obj);
		}
	}

	_listButton.at(0)->Update(obj);
	_listButton.at(1)->Update(obj);
	_listButton.at(2)->Update(obj);

}

void BaseChooseScene::InitializeComponent()
{
	
	orxVECTOR pos;
	pos.fX = BEGIN_X;
	pos.fY = BEGIN_Y;
	pos.fZ = 1.0;

    InitializePreview(pos);

    orxLOG("%d",sizeof(_arrPreview));
	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
		pos.fX = -75.0;
        pos.fY = (-BEGIN_Y) + 50.0;
		FFButton* btn = new FFButton(this,pos,"Back",(BUTTONCLICK)&BaseChooseScene::OnBackClick);
		_listButton.push_back(btn);
	}

    orxVECTOR scale;
    scale.fX = 1.5;
    scale.fY = 1.5;
	orxConfig_Clear();
	if(orxConfig_Load(BTN_LEFT_FILE) == orxSTATUS_SUCCESS)
	{
        pos.fX = -425;
        pos.fY = -10;
        FFButton* btn = new FFButton(this,pos,NULL,(BUTTONCLICK)&BaseChooseScene::OnLeftClick);
        btn->SetScale(&scale);
        _listButton.push_back(btn);
	}
	orxConfig_Clear();
	if(orxConfig_Load(BTN_RIGHT_FILE) == orxSTATUS_SUCCESS)
	{
        pos.fX = 400;
        FFButton* btn = new FFButton(this,pos,NULL,(BUTTONCLICK)&BaseChooseScene::OnRightClick);
        btn->SetScale(&scale);
        _listButton.push_back(btn);

	}
	
}

void BaseChooseScene::ShowGUI()
{
    for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            if(_arrPreview[i][j]._preview != NULL)
                _arrPreview[i][j]._preview->Show();
		}
	}
	for(size_t i = 0; i < _listButton.size(); i++)
	{
        _listButton.at(i)->Show();
	}
}

void BaseChooseScene::HideGUI()
{
    for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            if(_arrPreview[i][j]._preview != NULL)
                _arrPreview[i][j]._preview->Hide();
		}
	}
	for(size_t i = 0; i < _listButton.size(); i++)
	{
        _listButton.at(i)->Hide();
	}
}

void BaseChooseScene::OnShow()
{
	SceneEvent ev(FFUE_UI_SCENE_SHOW,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}

void BaseChooseScene::OnClose()
{
	SceneEvent ev(FFUE_UI_SCENE_CLOSE,_gameManager,this);
	orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&ev);
}


void BaseChooseScene::OnBackClick()
{
    HideGUI();
	OnClose();
}

void BaseChooseScene::OnLeftClick()
{
    if(_arrPreview[2][4]._preview == NULL || _arrPreview[2][4]._preview->GetNumber() == _maxCount)
        return;
    ShiftLeft();
}

void BaseChooseScene::OnRightClick()
{
    if(_arrPreview[0][0]._preview == NULL || !_arrPreview[0][0]._preview->GetNumber())
        return;
    ShiftRight();
}

void BaseChooseScene::ShiftLeft()
{
    int count = _arrPreview[2][4]._preview->GetNumber();
    count++;
    for(int i = 0;i < ROWS;i++)
    {
        if(_arrPreview[i][0]._preview)
        {
            delete _arrPreview[i][0]._preview;
            _arrPreview[i][0]._preview = NULL;
        }
    }

    for(int i = 0; i < COLS - 1;i++)
    {
        for(int j = 0; j < ROWS;j++)
        {
            _arrPreview[j][i]._preview = _arrPreview[j][i+1]._preview;
            _arrPreview[j][i]._preview->SetPosition(&_arrPreview[j][i]._pos);
            _arrPreview[j][i+1]._preview = NULL;
        }
    }

    InitializeRightColumn(count);
}

void BaseChooseScene::ShiftRight()
{
    int count = _arrPreview[0][0]._preview->GetNumber();
    count--;
    for(int i = 0;i < ROWS;i++)
    {
        if(_arrPreview[i][4]._preview)
        {
            delete _arrPreview[i][4]._preview;
            _arrPreview[i][4]._preview = NULL;
        }
    }

    for(int i = COLS-1; i > 0;i--)
    {
        for(int j = 0; j < ROWS ;j++)
        {
            _arrPreview[j][i]._preview = _arrPreview[j][i-1]._preview;
            _arrPreview[j][i]._preview->SetPosition(&_arrPreview[j][i]._pos);
            _arrPreview[j][i-1]._preview = NULL;
        }
    }

    InitializeLeftColumn(count);
}