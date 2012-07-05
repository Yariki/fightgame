#include "ChooseScene.h"

#define BEGIN_X -375.0
#define BEGIN_Y -225.0

#define DELTA_X 150.0
#define DELTA_Y 150.0


ChooseScene::ChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
    :FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;
    _maxCount = 20;

	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            _arrPreview[i][j]._preview =  NULL;
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

orxSTATUS ChooseScene::Update(const orxCLOCK_INFO* pClockInfo)
{
	orxVECTOR vPos;
	if(orxRender_GetWorldPosition(orxMouse_GetPosition(&vPos),&vPos))
	{
		orxOBJECT* obj = orxObject_Pick(&vPos);
		for(int i = 0; i < ROWS; i++)
		{
			for(int j = 0; j < COLS; j++)
			{
                if(_arrPreview[i][j]._preview != NULL)
                    _arrPreview[i][j]._preview->Update(obj);
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
        int count = 1;
        
		for(int i = 0; i < ROWS; i++)
		{
			for(int j = 0; j < COLS; j++)
			{
                _arrPreview[i][j]._preview= new FFPreview(NULL,pos,NULL,count++);
                _arrPreview[i][j]._pos = pos;
				pos.fX += DELTA_X;
			}
			pos.fX = BEGIN_X;
			pos.fY += DELTA_Y;
		}
        orxLOG("%d",sizeof(_arrPreview));
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
            btn = new FFButton(this,pos,"<<<",(BUTTONCLICK)&ChooseScene::OnLeftClick);
            btn->SetScale(&scale);
            _listButton.push_back(btn);
            pos.fX = 400;
            btn = new FFButton(this,pos,">>>",(BUTTONCLICK)&ChooseScene::OnRightClick);
            btn->SetScale(&scale);
            _listButton.push_back(btn);

		}
	}
}

void ChooseScene::ShowGUI()
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

void ChooseScene::HideGUI()
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
    if(_arrPreview[2][4]._preview == NULL || _arrPreview[2][4]._preview->GetNumber() == _maxCount)
        return;
    ShiftLeft();
}

void ChooseScene::OnRightClick()
{
    if(_arrPreview[0][0]._preview == NULL || _arrPreview[0][0]._preview->GetNumber() == 1)
        return;
    ShiftRight();
}

void ChooseScene::ShiftLeft()
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
    for(int i = 0;i < ROWS; i++)
    {
        _arrPreview[i][4]._preview = NULL;
        if(count <= _maxCount)
            _arrPreview[i][4]._preview = new FFPreview(this,_arrPreview[i][4]._pos,NULL,count++);
    }
}

void ChooseScene::ShiftRight()
{
    int count = _arrPreview[0][0]._preview->GetNumber();
    
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
    for(int i = ROWS-1;i >= 0; i--)
    {
        _arrPreview[i][0]._preview = NULL;
        int j = _arrPreview[i][1]._preview != NULL ? _arrPreview[i][1]._preview->GetNumber() - 1 : 0; 
        if(count > 0)
            _arrPreview[i][0]._preview = new FFPreview(this,_arrPreview[i][0]._pos,NULL,j);
    }
}