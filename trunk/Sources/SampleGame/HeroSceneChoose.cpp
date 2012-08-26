#include "HeroSceneChoose.h"

#define FIRST_SELECTOR "../Data/Ini/TemplateSelectFirstHero.ini"
#define SECOND_SELECTOR "../Data/Ini/TemplateSelectSecondHero.ini"

#define MAX_SELECTOR 2


HeroSceneChoose::HeroSceneChoose(FFGameManager* gameManager, FF_DISPLAY_SIZE& size)
	:BaseChooseScene(gameManager,size)
{
	_maxCount = _gameManager != NULL ? _gameManager->GetHeroPreviewList()->size() : 0;
	_currentChoose = -1;
}


HeroSceneChoose::~HeroSceneChoose(void)
{
	Unload();
}

orxSTATUS HeroSceneChoose::Unload()
{
	SAFEDELETE(_radioButtonGroup);

	for(int i = 0;i < COLS;i++)
		for(int j =0; j< ROWS;j++)
		{
			if(_arrPreview[j][i]._preview)
			{
				_arrPreview[j][i]._preview->UnlinkObject(_selectors.at(0)->GetSelector());
				_arrPreview[j][i]._preview->UnlinkObject(_selectors.at(1)->GetSelector());
			}
		}

		for(size_t i = 0; i < _selectors.size(); i++)
		{
			delete _selectors.at(i);
			_selectors.at(i) = NULL;
		}
		_selectors.clear();

		return __super::Unload();
}



void HeroSceneChoose::InitializeComponent()
{
	__super::InitializeComponent();

	if(orxConfig_Load(BTNS_FILE) == orxSTATUS_SUCCESS)
	{
		FFVector3 pos;
		pos._x = BEGIN_X;
		pos._y = BEGIN_Y - 60;
		pos._z = 0;
		_radioButtonGroup = new FFRadioButtonGroup(this,pos,NULL);
		_radioButtonGroup->AddItem(string("Choose FIRST  HERO!"));
		_radioButtonGroup->AddItem(string("Choose SECOND  HERO!"));
	}
	if(orxConfig_Load(FIRST_SELECTOR) == orxSTATUS_SUCCESS)
	{
		SelectorHero* sel = new SelectorHero(FIRST_SELECTOR);
		_selectors.push_back(sel);
	}
	if(orxConfig_Load(SECOND_SELECTOR) == orxSTATUS_SUCCESS)
	{
		SelectorHero* sel = new SelectorHero(SECOND_SELECTOR);
		_selectors.push_back(sel);
	}
}

void HeroSceneChoose::InitializePreview(FFVector3& pos)
{
	int count = 0;
	const std::vector<std::string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	if(list != NULL)
	{
		for(int j = 0; j < COLS; j++)
		{
			for(int i = 0; i < ROWS; i++)
			{
				if(count < _maxCount)
				{
					string scene = list->at(count);
					const orxCHAR* filename = scene.c_str();
					_arrPreview[i][j]._preview= new FFPreview(this,pos,NULL,filename,(ITEMCHOOSE)&HeroSceneChoose::OnPreviewChoose,count++);
					_arrPreview[i][j]._pos = pos;

				}
				else
				{
					_arrPreview[i][j]._preview= NULL;
					_arrPreview[i][j]._pos = pos;
				}
				pos._y += DELTA_Y;

			}
			pos._y = BEGIN_Y;
			pos._x += DELTA_X;
		}
	}
}


void HeroSceneChoose::InitializeLeftColumn(int i)
{
	int count = i;
	const std::vector<string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	for(int i = ROWS-1;i >= 0; i--)
	{
		_arrPreview[i][0]._preview = NULL;
		if(!list || count == -1)
			continue;
		string scene = list->at(count);
		if(scene.length() == 0)
			continue;
		const orxCHAR* filename = scene.c_str();
		_arrPreview[i][0]._preview = new FFPreview(this,_arrPreview[i][0]._pos,NULL,filename,(ITEMCHOOSE)&HeroSceneChoose::OnPreviewChoose,count--);
	}
}

void HeroSceneChoose::InitializeRightColumn(int i)
{
	int count = i;
	const std::vector<string>* list = _gameManager != NULL ? _gameManager->GetHeroPreviewList() : NULL;
	for(int i = 0;i < ROWS; i++)
	{
		_arrPreview[i][4]._preview = NULL;
		if(!list || count >= _maxCount)
			continue;
		string scene = list->at(count);
		if(scene.length() == 0 )
			continue;
		const orxCHAR* filename = scene.c_str();
		_arrPreview[i][4]._preview = new FFPreview(this,_arrPreview[i][4]._pos,NULL,filename,(ITEMCHOOSE)&HeroSceneChoose::OnPreviewChoose,count++);
	}
}


void HeroSceneChoose::ShowGUI()
{
	__super::ShowGUI();
	if(_radioButtonGroup)
		_radioButtonGroup->Show();
}

void HeroSceneChoose::HideGUI()
{
	__super::HideGUI();
	if(_radioButtonGroup)
		_radioButtonGroup->Hide();
}


void HeroSceneChoose::UpdateGUI(orxOBJECT* obj)
{
	if(_radioButtonGroup)
	{
		_radioButtonGroup->Update(obj);
		_currentChoose = _radioButtonGroup->GetCurrentItemIndex();
	}
	__super::UpdateGUI(obj);
	
}

void HeroSceneChoose::OnPreviewChoose(int index)
{
	if(index >= _maxCount)
		return;
	// unlink current selector object
	orxOBJECT* objUnlink = (_currentChoose > -1 && _currentChoose < MAX_SELECTOR) ? _selectors.at(_currentChoose)->GetSelector(): NULL;

	if(objUnlink)
	{
		_selectors.at(_currentChoose)->Hide();
		for(int i = 0;i < COLS;i++)
			for(int j =0; j< ROWS;j++)
			{
				if(_arrPreview[j][i]._preview)
					_arrPreview[j][i]._preview->UnlinkObject(objUnlink);
			}
	}
	
	// end unlink and now we try link object to preview

	if(_arrPreview[0][0]._preview == NULL)
		return;
	int numb = _arrPreview[0][0]._preview->GetNumber();
	int col = (index - numb) / ROWS;
	int row = index - (col * ROWS);
	if(col < COLS && row < ROWS && 
		_currentChoose > -1 && _currentChoose < MAX_SELECTOR)
	{
		_arrPreview[row][col]._preview->LinkObject( _selectors.at(_currentChoose)->GetSelector());
		_selectors.at(_currentChoose)->Show();

		FF_UI_EVENT ev;
		switch(_currentChoose)
		{
		case 0:
			ev = FFUE_FIRST_HERO_CHOOSE;
			break;
		case 1:
			ev = FFUE_SECOND_HERO_CHOOSE;
			break;
		}
		ChooseHeroEvent e(ev,index);
		orxEVENT_SEND(orxEVENT_TYPE_USER_DEFINED,0,this,orxNULL,&e);
	}
}