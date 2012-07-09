#include "ChooseScene.h"

#define BEGIN_X -375.0
#define BEGIN_Y -225.0

#define DELTA_X 150.0
#define DELTA_Y 150.0

#define BTN_LEFT_FILE "../Data/Ini/ButtonsLeft.ini"
#define BTN_RIGHT_FILE "../Data/Ini/ButtonsRight.ini"


ChooseScene::ChooseScene(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
    :FFBaseUiScene(gameManager,size)
{
	_type = FFST_UISCENE;
    _maxCount = _gameManager != NULL ? _gameManager->GetGameSceneList()->size() : 0;

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

void ChooseScene::UpdateGUI(orxOBJECT* obj)
{
	for(int i = 0; i < ROWS; i++)
	{
		for(int j = 0; j < COLS; j++)
		{
            if(_arrPreview[i][j]._preview != NULL)
                _arrPreview[i][j]._preview->Update(obj);
		}
	}
	//for(size_t i = 0; i < _listButton.size(); i++)
	//{
	//	_listButton.at(i)->Update(obj);
	//}
	_listButton.at(0)->Update(obj);
	_listButton.at(1)->Update(obj);
	_listButton.at(2)->Update(obj);

}

void ChooseScene::InitializeComponent()
{
	
	orxVECTOR pos;
	pos.fX = BEGIN_X;
	pos.fY = BEGIN_Y;
	pos.fZ = 0.0;
    int count = 0;
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    if(list != NULL)
    {
	    for(int j = 0; j < COLS; j++)
	    {
		    for(int i = 0; i < ROWS; i++)
		    {
                if(count < _maxCount)
                {
                    FFGameScene* scene = list->at(count);
                    std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
                    const orxCHAR* filename = f.c_str();
                    _arrPreview[i][j]._preview= new FFPreview(NULL,pos,NULL,filename,count++);
                    _arrPreview[i][j]._pos = pos;
			        
                }
                else
                {
                    _arrPreview[i][j]._preview= NULL;
                    _arrPreview[i][j]._pos = pos;
                }
                pos.fY += DELTA_Y;
                
		    }
		    pos.fY = BEGIN_Y;
		    pos.fX += DELTA_X;
	    }
    }
    orxLOG("%d",sizeof(_arrPreview));
	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
		pos.fX = -75.0;
        pos.fY = (-BEGIN_Y) + 50.0;
		FFButton* btn = new FFButton(this,pos,"Back",(BUTTONCLICK)&ChooseScene::OnBackClick);
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
        FFButton* btn = new FFButton(this,pos,NULL,(BUTTONCLICK)&ChooseScene::OnLeftClick);
        btn->SetScale(&scale);
        _listButton.push_back(btn);
	}
	orxConfig_Clear();
	if(orxConfig_Load(BTN_RIGHT_FILE) == orxSTATUS_SUCCESS)
	{
        pos.fX = 400;
        FFButton* btn = new FFButton(this,pos,NULL,(BUTTONCLICK)&ChooseScene::OnRightClick);
        btn->SetScale(&scale);
        _listButton.push_back(btn);

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
    if(_arrPreview[0][0]._preview == NULL || !_arrPreview[0][0]._preview->GetNumber())
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
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    for(int i = 0;i < ROWS; i++)
    {
        _arrPreview[i][4]._preview = NULL;
        if(!list || count >= _maxCount)
            continue;
        FFGameScene* scene = list->at(count);
        if(!scene)
            continue;
        std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
        const orxCHAR* filename = f.c_str();
        _arrPreview[i][4]._preview = new FFPreview(this,_arrPreview[i][4]._pos,NULL,filename,count++);
    }
}

void ChooseScene::ShiftRight()
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
    const std::vector<FFGameScene*>* list = _gameManager != NULL ? _gameManager->GetGameSceneList() : NULL;
    for(int i = ROWS-1;i >= 0; i--)
    {
        _arrPreview[i][0]._preview = NULL;
         if(!list || count == -1)
            continue;
        FFGameScene* scene = list->at(count);
        if(!scene)
            continue;
        std::string f = scene != NULL ? scene ->GetPreviewFileName().c_str() : "";
        const orxCHAR* filename = f.c_str();
        _arrPreview[i][0]._preview = new FFPreview(this,_arrPreview[i][0]._pos,NULL,filename,count--);
    }
}